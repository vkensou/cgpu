#pragma once

#include "stdint.h"

typedef struct oval_color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} oval_color_t;

typedef struct oval_point_t {
    float x;
    float y;
} oval_point_t;

typedef void (*oval_on_draw)(struct oval_device_t* device);

typedef struct oval_device_t {
    uint16_t width;
    uint16_t height;
    oval_on_draw on_draw;
} oval_device_t;

oval_device_t* oval_create_device(uint16_t width, uint16_t height, oval_on_draw on_draw);
void oval_runloop(oval_device_t* device);
void oval_free_device(oval_device_t* device);

void oval_draw_clear(oval_device_t* device, oval_color_t color);
void oval_draw_lines(oval_device_t* device, oval_point_t* points, uint32_t count);
void oval_draw_polygon(oval_device_t* device, oval_point_t* points, uint32_t count);
void oval_draw_commit(oval_device_t* device);
