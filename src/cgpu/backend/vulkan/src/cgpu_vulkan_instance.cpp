#include "common_utils.h"
#include "vulkan_utils.h"
#include "cgpu_vulkan_exts.h"
#include <vector>
#include <algorithm>
#include <string>

#include "parallel_hashmap/phmap.h"

class VkUtil_Blackboard
{
public:
    VkUtil_Blackboard(CGPUInstanceDescriptor const* desc)
    {
        const CGPUVulkanInstanceDescriptor* exts_desc = (const CGPUVulkanInstanceDescriptor*)desc->chained;
        // default
        device_extensions.insert(device_extensions.end(),
        std::begin(cgpu_wanted_device_exts), std::end(cgpu_wanted_device_exts));
        instance_extensions.insert(instance_extensions.end(),
        std::begin(cgpu_wanted_instance_exts), std::end(cgpu_wanted_instance_exts));
        // from desc
        if (desc->enable_debug_layer)
        {
            instance_layers.push_back(validation_layer_name);
        }
        if (desc->enable_set_name)
        {
            instance_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            instance_extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        }
        // Merge All Parameters into one blackboard
        if (exts_desc != CGPU_NULLPTR) // Extensions
        {
            if (exts_desc->backend != CGPU_BACKEND_VULKAN)
            {
                cgpu_assert(exts_desc->backend == CGPU_BACKEND_VULKAN && "Chained Instance Descriptor must have a vulkan backend!");
                exts_desc = CGPU_NULLPTR;
            }
            else
            {
                messenger_info_ptr = exts_desc->pDebugUtilsMessenger;
                report_info_ptr = exts_desc->pDebugReportMessenger;
                // Merge Instance Extension Names
                if (exts_desc->ppInstanceExtensions != NULL && exts_desc->mInstanceExtensionCount != 0)
                {
                    instance_extensions.insert(instance_extensions.end(),
                    exts_desc->ppInstanceExtensions, exts_desc->ppInstanceExtensions + exts_desc->mInstanceExtensionCount);
                }
                // Merge Instance Layer Names
                if (exts_desc->ppInstanceLayers != NULL && exts_desc->mInstanceLayerCount != 0)
                {
                    instance_layers.insert(instance_layers.end(),
                    exts_desc->ppInstanceLayers, exts_desc->ppInstanceLayers + exts_desc->mInstanceLayerCount);
                }
                // Merge Device Extension Names
                if (exts_desc->ppDeviceExtensions != NULL && exts_desc->mDeviceExtensionCount != 0)
                {
                    device_extensions.insert(device_extensions.end(),
                        exts_desc->ppDeviceExtensions,
                        exts_desc->ppDeviceExtensions + exts_desc->mDeviceExtensionCount);
                }
            }
        }
    }
    const VkDebugUtilsMessengerCreateInfoEXT* messenger_info_ptr = CGPU_NULLPTR;
    const VkDebugReportCallbackCreateInfoEXT* report_info_ptr = CGPU_NULLPTR;
    std::vector<const char*> instance_extensions;
    std::vector<const char*> instance_layers;
    std::vector<const char*> device_extensions;
    std::vector<const char*> device_layers;
};

struct CGPUVkExtensionsTable : public phmap::flat_hash_map<std::string, bool, std::hash<std::string>> //
{
    static void ConstructForAllAdapters(struct CGPUInstance_Vulkan* I, const VkUtil_Blackboard& blackboard)
    {
        const CGPUAllocator* allocator = &I->super.allocator;
        // enum physical devices & store informations.
        auto wanted_device_extensions = blackboard.device_extensions.data();
        const auto wanted_device_extensions_count = (uint32_t)blackboard.device_extensions.size();
        // construct extensions table
        for (uint32_t i = 0; i < I->mPhysicalDeviceCount; i++)
        {
            auto& Adapter = I->pVulkanAdapters[i];
            Adapter.pExtensionsTable = cgpu_new<CGPUVkExtensionsTable>(allocator);
            auto& Table = *Adapter.pExtensionsTable;
            for (uint32_t j = 0; j < wanted_device_extensions_count; j++)
            {
                Table[wanted_device_extensions[j]] = false;
            }
            for (uint32_t j = 0; j < Adapter.mExtensionsCount; j++)
            {
                const auto extension_name = Adapter.pExtensionNames[j];
                Table[extension_name] = true;
            }
            // Cache
            {
                Adapter.buffer_device_address = Table[VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME];
                Adapter.descriptor_buffer = Table[VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME];
                Adapter.descriptor_indexing = Table[VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME];

                Adapter.debug_marker = Table[VK_EXT_DEBUG_MARKER_EXTENSION_NAME];
                Adapter.dedicated_allocation = Table[VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME];
                Adapter.memory_req2 = Table[VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME];
                Adapter.external_memory = Table[VK_KHR_EXTERNAL_MEMORY_EXTENSION_NAME];
#ifdef _WIN32
                Adapter.external_memory_win32 = Table[VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME];
                Adapter.external_memory &= Adapter.external_memory_win32;
#endif
                Adapter.draw_indirect_count = Table[VK_KHR_DRAW_INDIRECT_COUNT_EXTENSION_NAME];
                Adapter.amd_draw_indirect_count = Table[VK_AMD_DRAW_INDIRECT_COUNT_EXTENSION_NAME];
                Adapter.amd_gcn_shader = Table[VK_AMD_GCN_SHADER_EXTENSION_NAME];
                Adapter.sampler_ycbcr = Table[VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME];
                
#ifdef ENABLE_NSIGHT_AFTERMATH
                Adapter.nv_diagnostic_checkpoints = Table[VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME];
                Adapter.nv_diagnostic_config = Table[VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME];
#endif
            }
        }
    }
    static void ConstructForInstance(struct CGPUInstance_Vulkan* I, const VkUtil_Blackboard& blackboard)
    {
        const CGPUAllocator* allocator = &I->super.allocator;
        // enum physical devices & store informations.
        auto wanted_instance_extensions = blackboard.instance_extensions.data();
        const auto wanted_instance_extensions_count = (uint32_t)blackboard.instance_extensions.size();
        // construct extensions table
        I->pExtensionsTable = cgpu_new<CGPUVkExtensionsTable>(allocator);
        auto& Table = *I->pExtensionsTable;
        for (uint32_t j = 0; j < wanted_instance_extensions_count; j++)
        {
            const auto key = wanted_instance_extensions[j];
            Table.insert_or_assign(key, false);
        }
        for (uint32_t j = 0; j < I->mExtensionsCount; j++)
        {
            const auto key = I->pExtensionNames[j];
            Table.insert_or_assign(key, true);
        }
        // Cache
        {
            I->device_group_creation = Table[VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME]; // Linked GPU
            I->debug_utils = Table[VK_EXT_DEBUG_UTILS_EXTENSION_NAME];
            I->debug_report = !I->debug_utils && Table[VK_EXT_DEBUG_REPORT_EXTENSION_NAME];
        }
    }
};

struct CGPUVkLayersTable : public phmap::flat_hash_map<std::string, bool, std::hash<std::string>> //
{
    static void ConstructForAllAdapters(struct CGPUInstance_Vulkan* I, const VkUtil_Blackboard& blackboard)
    {
        const CGPUAllocator* allocator = &I->super.allocator;
        // enum physical devices & store informations.
        auto wanted_device_layers = blackboard.device_layers.data();
        const auto wanted_device_layers_count = (uint32_t)blackboard.device_layers.size();
        // construct layers table
        for (uint32_t i = 0; i < I->mPhysicalDeviceCount; i++)
        {
            auto& Adapter = I->pVulkanAdapters[i];
            Adapter.pLayersTable = cgpu_new<CGPUVkLayersTable>(allocator);
            auto& Table = *Adapter.pLayersTable;
            for (uint32_t j = 0; j < wanted_device_layers_count; j++)
            {
                Table[wanted_device_layers[j]] = false;
            }
            for (uint32_t j = 0; j < Adapter.mLayersCount; j++)
            {
                Table[Adapter.pLayerNames[j]] = true;
            }
        }
    }
    static void ConstructForInstance(struct CGPUInstance_Vulkan* I, const VkUtil_Blackboard& blackboard)
    {
        const CGPUAllocator* allocator = &I->super.allocator;
        // enum physical devices & store informations.
        auto wanted_instance_layers = blackboard.instance_layers.data();
        const auto wanted_instance_layers_count = (uint32_t)blackboard.instance_layers.size();
        // construct layers table
        I->pLayersTable = cgpu_new<CGPUVkLayersTable>(allocator);
        auto& Table = *I->pLayersTable;
        for (uint32_t j = 0; j < wanted_instance_layers_count; j++)
        {
            Table[wanted_instance_layers[j]] = false;
        }
        for (uint32_t j = 0; j < I->mLayersCount; j++)
        {
            Table[I->pLayerNames[j]] = true;
        }
    }
};

CGPUInstanceId cgpu_create_instance_vulkan(CGPUInstanceDescriptor const* desc)
{
    // Merge All Parameters into one blackboard
    const VkUtil_Blackboard blackboard(desc);

    cgpu_malloc_fn malloc_fn;
    cgpu_realloc_fn realloc_fn;
    cgpu_calloc_fn calloc_fn;
    cgpu_free_fn free_fn;
    cgpu_malloc_aligned_fn malloc_aligned_fn;
    cgpu_realloc_aligned_fn realloc_aligned_fn;
    cgpu_calloc_aligned_fn calloc_aligned_fn;
    cgpu_free_aligned_fn free_aligned_fn;
    if (desc->allocator.malloc_fn && desc->allocator.calloc_fn && desc->allocator.free_fn)
    {
        malloc_fn = desc->allocator.malloc_fn;
        realloc_fn = desc->allocator.realloc_fn;
        calloc_fn = desc->allocator.calloc_fn;
        free_fn = desc->allocator.free_fn;
    }
    else
    {
        malloc_fn = cgpu_malloc_default;
        realloc_fn = cgpu_realloc_default;
        calloc_fn = cgpu_calloc_default;
        free_fn = cgpu_free_default;
    }
    if (desc->allocator.malloc_aligned_fn && desc->allocator.realloc_aligned_fn && desc->allocator.calloc_aligned_fn && desc->allocator.free_aligned_fn)
    {
        malloc_aligned_fn = desc->allocator.malloc_aligned_fn;
        realloc_aligned_fn = desc->allocator.realloc_aligned_fn;
        calloc_aligned_fn = desc->allocator.calloc_aligned_fn;
        free_aligned_fn = desc->allocator.free_aligned_fn;
    }
    else
    {
        malloc_aligned_fn = cgpu_malloc_aligned_default;
        realloc_aligned_fn = cgpu_realloc_aligned_default;
        calloc_aligned_fn = cgpu_calloc_aligned_default;
        free_aligned_fn = cgpu_free_aligned_default;
    }

    // Memory Alloc
    CGPUInstance_Vulkan* I = (CGPUInstance_Vulkan*)calloc_fn(desc->allocator.user_data, 1, sizeof(CGPUInstance_Vulkan), 0);
    ::memset(I, 0, sizeof(CGPUInstance_Vulkan));

    if (desc->logger.log_callback)
        I->super.logger.log_callback = desc->logger.log_callback;
    else
        I->super.logger.log_callback = logger_default;
    I->super.logger.log_callback_user_data = desc->logger.log_callback_user_data;

    I->super.allocator.malloc_fn = malloc_fn;
    I->super.allocator.realloc_fn = realloc_fn;
    I->super.allocator.calloc_fn = calloc_fn;
    I->super.allocator.free_fn = free_fn;
    I->super.allocator.malloc_aligned_fn = malloc_aligned_fn;
    I->super.allocator.realloc_aligned_fn = realloc_aligned_fn;
    I->super.allocator.calloc_aligned_fn = calloc_aligned_fn;
    I->super.allocator.free_aligned_fn = free_aligned_fn;
    I->super.allocator.user_data = desc->allocator.user_data;

    I->vkAllocator.pUserData = I;
    I->vkAllocator.pfnAllocation = cgpu_vulkan_alloc;
    I->vkAllocator.pfnReallocation = cgpu_vulkan_realloc;
    I->vkAllocator.pfnFree = cgpu_vulkan_free;
    I->vkAllocator.pfnInternalAllocation = cgpu_vulkan_internal_alloc_notify;
    I->vkAllocator.pfnInternalFree = cgpu_vulkan_internal_free_notify;

    // Initialize Environment
    VkUtil_InitializeEnvironment(&I->super);

    // Create VkInstance.
    CGPU_DECLARE_ZERO(VkApplicationInfo, appInfo)
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "CGPU";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

    uint32_t apiVersion;
    vkEnumerateInstanceVersion(&apiVersion);
    appInfo.apiVersion = apiVersion;
    I->apiVersion = apiVersion;

    // Select Instance Layers & Layer Extensions
    VkUtil_SelectInstanceLayers(I,
        blackboard.instance_layers.data(),
        (uint32_t)blackboard.instance_layers.size());
    // Select Instance Extensions
    VkUtil_SelectInstanceExtensions(I,
        blackboard.instance_extensions.data(),
        (uint32_t)blackboard.instance_extensions.size());

    CGPU_DECLARE_ZERO(VkInstanceCreateInfo, createInfo)
#if defined(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME) && defined(_MACOS)
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#endif
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    // Instance Layers
    createInfo.enabledLayerCount = I->mLayersCount;
    createInfo.ppEnabledLayerNames = I->pLayerNames;
    // Instance Extensions
    createInfo.enabledExtensionCount = I->mExtensionsCount;
    createInfo.ppEnabledExtensionNames = I->pExtensionNames;

    // List Validation Features
    CGPU_DECLARE_ZERO(VkValidationFeaturesEXT, validationFeaturesExt)
    validationFeaturesExt.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
    VkValidationFeatureEnableEXT enabledValidationFeatures[] = {
        VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
        VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
    };
    if (desc->enable_gpu_based_validation)
    {
        if (!desc->enable_debug_layer)
        {
            cgpu_warn(&(I->super.logger), "Vulkan GpuBasedValidation enabled while ValidationLayer is closed, there'll be no effect.\n");
        }
#if VK_HEADER_VERSION >= 108
        validationFeaturesExt.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
        validationFeaturesExt.enabledValidationFeatureCount = sizeof(enabledValidationFeatures) / sizeof(VkValidationFeatureEnableEXT);
        validationFeaturesExt.pEnabledValidationFeatures = enabledValidationFeatures;
        createInfo.pNext = &validationFeaturesExt;
#else
        cgpu_warn(&(I->super.logger), "Vulkan GpuBasedValidation enabled but VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT is not supported!\n");
#endif
    }

    auto instRes = (int32_t)vkCreateInstance(&createInfo, &I->vkAllocator, &I->pVkInstance);
    if (instRes != VK_SUCCESS)
    {
        cgpu_fatal(&(I->super.logger), "Vulkan: failed to create instance with code %d\n", instRes);
        cgpu_assert(0 && "Vulkan: failed to create instance!");
    }
    CGPUVkLayersTable::ConstructForInstance(I, blackboard);
    CGPUVkExtensionsTable::ConstructForInstance(I, blackboard);

#if defined(NX64)
    loadExtensionsNX(result->pVkInstance);
#else
    // Load Vulkan instance functions
    volkLoadInstance(I->pVkInstance);
#endif

    // enum physical devices & store informations.
    const char* const* wanted_device_extensions = blackboard.device_extensions.data();
    const auto wanted_device_extensions_count = (uint32_t)blackboard.device_extensions.size();
    const char* const* wanted_device_layers = blackboard.device_layers.data();
    const auto wanted_device_layers_count = (uint32_t)blackboard.device_layers.size();
    VkUtil_QueryAllAdapters(I,
        wanted_device_layers, wanted_device_layers_count,
        wanted_device_extensions, wanted_device_extensions_count);
    // sort by GPU type
    std::stable_sort(I->pVulkanAdapters, I->pVulkanAdapters + I->mPhysicalDeviceCount, 
    [](const CGPUAdapter_Vulkan& a, const CGPUAdapter_Vulkan& b) {
        const uint32_t orders[] = {
            4, 1, 0, 2, 3
        };
        return orders[a.mPhysicalDeviceProps.properties.deviceType] < orders[b.mPhysicalDeviceProps.properties.deviceType];
    });
    // construct extensions table
    CGPUVkLayersTable::ConstructForAllAdapters(I, blackboard);
    CGPUVkExtensionsTable::ConstructForAllAdapters(I, blackboard);

    // Open validation layer.
    if (desc->enable_debug_layer)
    {
        VkUtil_EnableValidationLayer(I, blackboard.messenger_info_ptr, blackboard.report_info_ptr);
    }

    return &(I->super);
}

void cgpu_free_instance_vulkan(CGPUInstanceId instance)
{
    CGPUInstance_Vulkan* to_destroy = (CGPUInstance_Vulkan*)instance;
    const CGPUAllocator* allocator = &instance->allocator;
    VkUtil_DeInitializeEnvironment(&to_destroy->super);
    if (to_destroy->pVkDebugUtilsMessenger)
    {
        cgpu_assert(vkDestroyDebugUtilsMessengerEXT && "Load vkDestroyDebugUtilsMessengerEXT failed!");
        vkDestroyDebugUtilsMessengerEXT(to_destroy->pVkInstance, to_destroy->pVkDebugUtilsMessenger, &to_destroy->vkAllocator);
    }

    vkDestroyInstance(to_destroy->pVkInstance, &to_destroy->vkAllocator);
    for (uint32_t i = 0; i < to_destroy->mPhysicalDeviceCount; i++)
    {
        auto& Adapter = to_destroy->pVulkanAdapters[i];
        cgpu_free(allocator, Adapter.pQueueFamilyProperties);
        // free extensions cache
        cgpu_delete(allocator, Adapter.pExtensionsTable);
        cgpu_free(allocator, Adapter.pExtensionNames);
        cgpu_free(allocator, Adapter.pExtensionProperties);

        // free layers cache
        cgpu_delete(allocator, Adapter.pLayersTable);
        cgpu_free(allocator, Adapter.pLayerNames);
        cgpu_free(allocator, Adapter.pLayerProperties);
    }
    // free extensions cache
    cgpu_delete(allocator, to_destroy->pExtensionsTable);
    cgpu_free(allocator, to_destroy->pExtensionNames);
    cgpu_free(allocator, to_destroy->pExtensionProperties);
    // free layers cache
    cgpu_delete(allocator, to_destroy->pLayersTable);
    cgpu_free(allocator, to_destroy->pLayerNames);
    cgpu_free(allocator, to_destroy->pLayerProperties);

    cgpu_free(allocator, to_destroy->pVulkanAdapters);
    cgpu_free(allocator, to_destroy);
}

const float queuePriorities[] = {
    1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, //
    1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, //
    1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, //
    1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, //
};
CGPUDeviceId cgpu_create_device_vulkan(CGPUAdapterId adapter, const CGPUDeviceDescriptor* desc)
{
    CGPUInstance_Vulkan* I = (CGPUInstance_Vulkan*)adapter->instance;
    const CGPUAllocator* allocator = &adapter->instance->allocator;
    CGPUDevice_Vulkan* D = (CGPUDevice_Vulkan*)cgpu_calloc(allocator, 1, sizeof(CGPUDevice_Vulkan));
    CGPUAdapter_Vulkan* A = (CGPUAdapter_Vulkan*)adapter;

    *const_cast<CGPUAdapterId*>(&D->super.adapter) = adapter;

    // Prepare Create Queues
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    queueCreateInfos.resize(desc->queue_group_count);
    for (uint32_t i = 0; i < desc->queue_group_count; i++)
    {
        VkDeviceQueueCreateInfo& info = queueCreateInfos[i];
        CGPUQueueGroupDescriptor& descriptor = desc->queue_groups[i];
        info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        info.queueCount = descriptor.queue_count;
        info.queueFamilyIndex = (uint32_t)A->mQueueFamilyIndices[descriptor.queue_type];
        info.pQueuePriorities = queuePriorities;

        cgpu_assert(info.queueCount <= A->pQueueFamilyProperties[info.queueFamilyIndex].queueCount && "allocated too many queues!");
    }
    // Create Device
    CGPU_DECLARE_ZERO(VkDeviceCreateInfo, createInfo)
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    if (vkGetPhysicalDeviceFeatures2KHR || I->apiVersion >= VK_API_VERSION_1_1)
        createInfo.pNext = &A->mPhysicalDeviceFeatures;
    else
        createInfo.pEnabledFeatures = &A->mPhysicalDeviceFeatures.features;
    createInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.enabledExtensionCount = A->mExtensionsCount;
    createInfo.ppEnabledExtensionNames = A->pExtensionNames;
    createInfo.enabledLayerCount = A->mLayersCount;
    createInfo.ppEnabledLayerNames = A->pLayerNames;

    VkResult result = vkCreateDevice(A->pPhysicalDevice, &createInfo, &I->vkAllocator, &D->pVkDevice);
    if (result != VK_SUCCESS)
    {
        cgpu_assert(0 && "failed to create logical device!");
    }

    // Single Device Only.
    volkLoadDeviceTable(&D->mVkDeviceTable, D->pVkDevice);
    cgpu_assert(D->mVkDeviceTable.vkCreateSwapchainKHR && "failed to load swapchain proc!");

    // Create Pipeline Cache
    D->pPipelineCache = VK_NULL_HANDLE;
    if (!desc->disable_pipeline_cache)
    {
        VkUtil_CreatePipelineCache(D);
    }

    // Create VMA Allocator
    VkUtil_CreateVMAAllocator(I, A, D);
    // Create Descriptor Heap
    D->pDescriptorPool = VkUtil_CreateDescriptorPool(D);

    VkUtil_EnsureFeatures(A, D);

    return &D->super;
}

void cgpu_free_device_vulkan(CGPUDeviceId device)
{
    CGPUDevice_Vulkan* D = (CGPUDevice_Vulkan*)device;
    CGPUAdapter_Vulkan* A = (CGPUAdapter_Vulkan*)device->adapter;
    CGPUInstance_Vulkan* I = (CGPUInstance_Vulkan*)device->adapter->instance;
    CGPUAllocator* allocator = &I->super.allocator;

    for (uint32_t i = 0; i < VK_MAX_MEMORY_TYPES; i++)
    {
        if (D->pExternalMemoryVmaPools[i])
        {
            vmaDestroyPool(D->pVmaAllocator, D->pExternalMemoryVmaPools[i]);
        }
        if (D->pExternalMemoryVmaPoolNexts[i])
        {
            cgpu_free(allocator, D->pExternalMemoryVmaPoolNexts[i]);
        }
    }
    VkUtil_FreeVMAAllocator(I, A, D);
    VkUtil_FreeDescriptorPool(D->pDescriptorPool);
    VkUtil_FreePipelineCache(I, A, D);
    vkDestroyDevice(D->pVkDevice, &I->vkAllocator);
    cgpu_free(allocator, D);
}