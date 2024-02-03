#include <iostream>
#include "oval_device.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static void on_draw(oval_device_t* device) {
	auto clearcolor = oval_color_t {
		.r = 255,
		.g = 0,
		.b = 0,
		.a = 255,
	};
	oval_draw_clear(device, clearcolor);
}

int main(int argc, char** argv)
{
	auto device = oval_create_device(SCREEN_WIDTH, SCREEN_HEIGHT, on_draw);
	if (device)
	{
		oval_runloop(device);
		oval_free_device(device);
	}

    return 0;
}