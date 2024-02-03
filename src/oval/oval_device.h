#pragma once

#include "stdint.h"

typedef struct oval_color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

typedef struct oval_point_t {
    float x;
    float y;
} oval_point_t;

typedef struct oval_device_t {
    uint16_t width;
    uint16_t height;
    void (*draw_clear)(oval_device_t* device, oval_color_t color);
    void (*draw_lines)(oval_device_t* device, oval_point_t* points, uint32_t count);
    void (*draw_commit)(oval_device_t* device);
} oval_device_t;