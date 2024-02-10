#include <iostream>
#include "oval_device.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

static void on_draw(oval_device_t* device) {
	auto clearcolor = oval_color_t {
		.r = 0,
		.g = 0,
		.b = 0,
		.a = 255,
	};
	oval_draw_clear(device, clearcolor);

	oval_point_t polygon[4] =
	{
		{ -0.5, 0.5},
		{ 0.5, 0.5},
		{ -0.5, -0.5},
		{ 0.5, -0.5},
	};
	oval_draw_polygon(device, polygon, 4);

	oval_point_t lines[5] =
	{
		{ -0.51, 0.51},
		{ -0.51, -0.51},
		{ 0.51, -0.51},
		{ 0.51, 0.51},
		{ -0.51, 0.51},
	};
	oval_draw_lines(device, lines, 5);
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