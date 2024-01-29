# 简介
本项目来源于：[SakuraEngine](https://github.com/SakuraEngine/SakuraEngine)。项目还在施工中……目前只移植了vulkan。

按照自己的品味做了一点修改：
* 必须显式创建RenderPass和Framebuffer，减少库内部的状态管理
* 添加logger和allocator接口
* 支持了vulkan 1.0，需要的扩展尽可能少，或者给出扩展不支持时的兼容措施

项目目标是：
* 纯C接口
* 足够底层和轻薄
* 只做跟抽象图形API有关的事
* 像logger、allocator等事情都提供接口由外部负责
* 手感贴近vulkan，但比vulkan简单
* 内部状态尽可能的少，把选择权留给调用方
