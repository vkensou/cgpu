#pragma once

#include "cgpu/api.h"
#include <vector>
#include <string>

struct TimeStampQuery
{
	CGPUQueryPoolId query_pool;
	CGPUBufferId query_buffer;
	std::vector<std::string> labels;
};

struct TimeStamp
{
	std::string label;
	float duration;
};

class GpuTimeStamps
{
public:
	GpuTimeStamps(CGPUDeviceId device, uint32_t frame_count);
	~GpuTimeStamps();
	void OnBeginFrame(CGPUCommandBufferId cmd, float gpuTicksPerSecond, std::vector<TimeStamp>& pTimestamps);
	void GetTimeStamp(CGPUCommandBufferId cmd, const char* label);
	void CollectTimings(CGPUCommandBufferId cmd);
	void OnEndFrame();

private:
	const uint32_t MaxValuesPerFrame = 128;

	uint32_t current_frame_index = 0;
	uint32_t frame_count;
	std::vector<TimeStampQuery> timeStampQueries;
};