#include "GpuTimeStamps.h"

GpuTimeStamps::GpuTimeStamps(CGPUDeviceId device, uint32_t frame_count)
	: frame_count(frame_count)
{
	for (int i = 0; i < frame_count; ++i)
	{
		CGPUQueryPoolDescriptor query_pool_desc = {
			.type = CGPU_QUERY_TYPE_TIMESTAMP,
			.query_count = frame_count * MaxValuesPerFrame,
		};
		auto query_pool = cgpu_create_query_pool(device, &query_pool_desc);

		CGPUBufferDescriptor query_buffer_desc = {
		   .size = sizeof(uint64_t) * MaxValuesPerFrame,
		   .name = u8"QueryBuffer",
		   .descriptors = CGPU_RESOURCE_TYPE_NONE,
		   .memory_usage = CGPU_MEM_USAGE_GPU_TO_CPU,
		   .flags = CGPU_BCF_PERSISTENT_MAP_BIT,
		   .start_state = CGPU_RESOURCE_STATE_UNDEFINED,
		};
		auto query_buffer = cgpu_create_buffer(device, &query_buffer_desc);

		TimeStampQuery query;
		query.query_pool = query_pool;
		query.query_buffer = query_buffer;
		query.labels.clear();

		timeStampQueries.push_back(query);
	}
}

GpuTimeStamps::~GpuTimeStamps()
{
	for (int i = 0; i < frame_count; ++i)
	{
		auto& query = timeStampQueries[i];
		cgpu_free_buffer(query.query_buffer);
		cgpu_free_query_pool(query.query_pool);
	}
}

void GpuTimeStamps::OnBeginFrame(CGPUCommandBufferId cmd, float gpuTicksPerSecond, std::vector<TimeStamp>& stamps)
{
	auto& query = timeStampQueries[current_frame_index];

	auto& gpuLabels = query.labels;

	stamps.clear();

	uint32_t numMeasurements = (uint32_t)gpuLabels.size();
	if (numMeasurements > 0)
	{
		double gpuTicksPerMicroSeconds = gpuTicksPerSecond * 1e-6;

		uint32_t ini = 0;

		auto query_buffer_ptr = (uint64_t*)(query.query_buffer->info->cpu_mapped_address);

		for (uint32_t i = 1; i < numMeasurements; ++i)
		{
			auto last_stamp = query_buffer_ptr[ini + i - 1];
			auto stamp = query_buffer_ptr[ini + i];
			stamps.push_back({ gpuLabels[i], (float)((stamp - last_stamp) * gpuTicksPerMicroSeconds) });
		}

		{
			auto first_stamp = query_buffer_ptr[ini];
			auto last_stamp = query_buffer_ptr[ini + numMeasurements - 1];
			stamps.push_back({ "Total GPU Time", (float)((last_stamp - first_stamp) * gpuTicksPerMicroSeconds) });
		}

		gpuLabels.clear();
	}

	cgpu_cmd_reset_query_pool(cmd, query.query_pool, current_frame_index * MaxValuesPerFrame, MaxValuesPerFrame);
}

void GpuTimeStamps::GetTimeStamp(CGPUCommandBufferId cmd, const char* label)
{
	auto& query = timeStampQueries[current_frame_index];
	uint32_t measurements = (uint32_t)query.labels.size();
	uint32_t offset = current_frame_index * MaxValuesPerFrame + measurements;

	CGPUQueryDescriptor query_desc = {
		.index = offset,
		.stage = CGPU_SHADER_STAGE_ALL_GRAPHICS,
	};
	cgpu_cmd_begin_query(cmd, query.query_pool, &query_desc);

	query.labels.push_back(label);
}

void GpuTimeStamps::CollectTimings(CGPUCommandBufferId cmd)
{
	auto& query = timeStampQueries[current_frame_index];
	cgpu_cmd_resolve_query(cmd, query.query_pool, query.query_buffer, current_frame_index * MaxValuesPerFrame, query.labels.size());
}

void GpuTimeStamps::OnEndFrame()
{
	current_frame_index = (current_frame_index + 1) % frame_count;
}
