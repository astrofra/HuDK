/*
 * This file is part of HuDK.
 * ASM and C open source software development kit for the NEC PC Engine.
 * Licensed under the MIT License
 * (c) 2016-2019 MooZ
 */
#ifndef HUDK_TOOLS_TILESET_H
#define HUDK_TOOLS_TILESET_H

#include "image.h"

typedef struct {
    uint8_t *tiles;
    int tile_count;
    int tile_width;
    int tile_height;
    uint8_t *palette_index;
    uint8_t *palette;
    int palette_count;
} tileset_t;

int tileset_create(tileset_t *tileset, int tile_count, int tile_width, int tile_height);

int tileset_add(tileset_t *tileset, int i, image_t *img, int x, int y);

void tileset_destroy(tileset_t *tileset);


#endif /* HUDK_TOOLS_TILESET_H */