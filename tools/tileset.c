/*
 * This file is part of HuDK.
 * ASM and C open source software development kit for the NEC PC Engine.
 * Licensed under the MIT License
 * (c) 2016-2019 MooZ
 */
#include "tileset.h"

#include "log.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int tileset_create(tileset_t *tileset, int tile_count, int tile_width, int tile_height) {
    memset(tileset, 0, sizeof(tileset_t));
    tileset->tile_count = tile_count;
    tileset->tile_width = tile_width;
    tileset->tile_height = tile_height;
    tileset->palette_index = (uint8_t*)malloc(tile_count * sizeof(uint8_t));
    tileset->tiles = (uint8_t*)malloc(tile_count * tile_width * tile_height * sizeof(uint8_t));
    if(!(tileset->palette_index && tileset->tiles)) {
        tileset_destroy(tileset);
        return 0;
    }
    return 1;
}

int tileset_add(tileset_t *tileset, int tile_index, image_t *img, int x, int y) {
    int i, j, k, l, t;
    int palette_index;
    
    if((tile_index >= tileset->tile_count) || ((x+8) >= img->width) || ((y+8) >= img->height) ||
       (x<0) || (y<0)){
        log_error("invalid parameter.");
        return 0;
    }

    // check that tile colors fits into a single palette.
    palette_index = img->data[x + (y * img->width)] / 16;
    if(palette_index >= 16) {
        log_error("invalid palette index: %d (max 16).", palette_index);
        return 0;
    }
    for(j=0; (j<tileset->tile_height) && ((y+j)<img->height); j++) {
        for(i=0; (i<tileset->tile_width) && ((x+i)<img->width); i++) {
            int col = img->data[x+i + ((y+j) * img->width)];
            int index = col /16;
            if(palette_index != index) {
                log_error("tile (%d,%d) color is out of palette bounds.", x+i, y+j);
                return 0;
            }
        }
    }
    tileset->palette_index[tile_index] = palette_index;
    
    if(palette_index >= tileset->palette_count) {
        uint8_t *tmp = (uint8_t*)realloc(tileset->palette, (palette_index+1)*3*16);
        if(tmp == NULL) {
            log_error("failed to resize palette.");
            return 0;
        }
        tileset->palette = tmp;
    }
    for(i=palette_index*16, j=0; (j<16) && (i<img->color_count); j++, i++) {
        tileset->palette[3*i  ] = img->palette[3*i  ];
        tileset->palette[3*i+1] = img->palette[3*i+1];
        tileset->palette[3*i+2] = img->palette[3*i+2];
    }

    // copy bitmaps.
    for(j=0, t=0; j<tileset->tile_height; j+=8) {
        for(i=0; i<tileset->tile_width; i+=8, t+=8) {
            for(l=0; l<8; l++) {
                for(k=0; k<8; k++) {
                    tileset->tiles[k+t + l*tileset->tile_width*tileset->tile_height] = img->data[x+i+k + (y+j+l)*img->width];
                }
            }
        }
    }
    return 1;
}

void tileset_destroy(tileset_t *tileset) {
    if(tileset->tiles) {
        free(tileset->tiles);
    }
    if(tileset->palette_index) {
        free(tileset->palette_index);
    }
    if(tileset->palette) {
        free(tileset->palette);
    }
    memset(&tileset, 0, sizeof(tileset_t));
}
