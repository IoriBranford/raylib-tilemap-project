#include "sprites.h"

#include <assert.h>
#include <math.h>

Texture* GetTileImage(tmx_tile *tile) {
    Texture* image = NULL;
    tmx_tileset *tileset = tile->tileset;

    tmx_image *im = tile->image;
    if (im && im->resource_image) {
        image = (Texture*)im->resource_image;
    }
    else if (tile->tileset->image->resource_image) {
        image = (Texture*)tileset->image->resource_image;
    }
    return image;
}

void GetTileSource(Rectangle *source, tmx_tile *tile) {
    source->x  = tile->ul_x;
    source->y  = tile->ul_y;
    source->width  = tile->tileset->tile_width;
    source->height = tile->tileset->tile_height;
}

void GetTileOrigin(Vector2 *origin, tmx_tile *tile, Vector2 destSize) {
    tmx_tileset *tileset = tile->tileset;

    Vector2 scale = {1, 1};
    if (destSize.x) scale.x = destSize.x / tileset->tile_width;
    if (destSize.y) scale.y = destSize.y / tileset->tile_height;

    origin->x = scale.x * -tileset->x_offset;
    origin->y = scale.y * (tileset->tile_height - tileset->y_offset);
}

void SetSpriteTile(Sprite *g, tmx_tile *tile) {
    Texture *image = GetTileImage(tile);
    if (image == NULL)
        return;

    g->tile.tile = tile;
    g->tile.texture = image;
    GetTileSource(&g->tile.source, tile);
    GetTileOrigin(&g->origin, tile, g->size);

    g->tile.frame = 0;
}

void UpdateSprite_Tile(Sprite *g) {
    tmx_tile *tile = g->tile.tile;
    tmx_anim_frame *anim = tile->animation;
    unsigned n = tile->animation_len;
    if (anim && n) {
        tmx_tile *tiles = tile->tileset->tiles;
        tmx_anim_frame *frame = anim + g->tile.frame;

        g->animTimer += GetFrameTime()*g->animSpeedMS;

        while (g->animTimer >= frame->duration) {
            g->animTimer -= frame->duration;
            ++g->tile.frame;
            g->tile.frame %= n;
            frame = anim + g->tile.frame;
            GetTileSource(&g->tile.source, tiles + frame->tile_id);
        }
    }
}

void DrawSprite_Tile(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TILE);
    DrawTexturePro(*g->tile.texture, g->tile.source, g->rect, g->origin, g->rotationDeg, g->color);
}

Sprite* NewTileSprite(tmx_tile *tile, Rectangle rect, float rotationDeg, Color color) {
    Sprite *g = NewSprite();
    if (g) {
        g->used = true;
        g->rect = rect;
        g->rotationDeg = rotationDeg;
        g->color = color;
        g->behavior.type = SPRITETYPE_TILE;
        g->behavior.update = UpdateSprite_Tile;
        g->behavior.draw = DrawSprite_Tile;
        g->animSpeedMS = 1000;
        SetSpriteTile(g, tile);
    }
    return g;
}

Sprite* NewTMXObjectSprite(tmx_object *o, tmx_tile **maptiles, Color color) {
    if (o->obj_type == OT_TILE) {
        int gid = o->content.gid;
        int i = gid & TMX_FLIP_BITS_REMOVAL;
        float flipx = (gid & TMX_FLIPPED_HORIZONTALLY) ? -1 : 1;
        float flipy = (gid & TMX_FLIPPED_VERTICALLY) ? -1 : 1;
        tmx_tile *tile = maptiles[i];
        Rectangle rect = {
            .x = o->x, .y = o->y,
            .width = flipx * o->width, .height = flipy * o->height
        };
        return NewTileSprite(tile, rect, o->rotation, color);
    } else if (o->obj_type == OT_SQUARE) {
        Rectangle rect = {
            .x = o->x, .y = o->y,
            .width = o->width, .height = o->height
        };
        Vector2 origin = { 0, 0 };
        return NewRectangleSprite(rect, origin, o->rotation, color);
    }

    return NULL;
}

void UpdateSprite_TileLayer(Sprite *g) {
    g->animTimer += GetFrameTime()*g->animSpeedMS;
}

void DrawSprite_TileLayer(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TILELAYER);
    tmx_map *map = g->layer.map;
    tmx_layer *layer = g->layer.layer;

    assert(layer->type == L_LAYER);

    uint32_t *gids = layer->content.gids;
    tmx_tile **mapTiles = map->tiles;
    
    unsigned cols = map->width;
    unsigned rows = map->height;
    unsigned colw = map->tile_width;
    unsigned rowh = map->tile_height;
    unsigned n = cols * rows;

    Rectangle source;
    Vector2 position = g->position;
    Rectangle rect = { position.x, position.y + rowh, colw, rowh };
    Vector2 origin = { 0, 0 }, size = { 0, 0 };
    Color color = ColorFromTMX(layer->tintcolor);

    unsigned col = 0, row = 0;
    for (unsigned i = 0; i < n; ++i) {
        uint32_t gid = *gids++;
        uint32_t tileId = gid & TMX_FLIP_BITS_REMOVAL;

        if (tileId) {
            tmx_tile *tile = mapTiles[tileId];

            tmx_anim_frame *anim = tile->animation;
            if (anim) {
                float totalDuration = 0;
                for (unsigned i = 0; i < tile->animation_len; ++i)
                    totalDuration += anim[i].duration;

                float animTime = fmodf(g->animTimer, totalDuration);

                for (unsigned i = 0; i < tile->animation_len; ++i) {
                    if (animTime < anim[i].duration) {
                        tile = tile->tileset->tiles + anim[i].tile_id;
                        break;
                    }
                    animTime -= anim[i].duration;
                }
            }

            rect.width = tile->width;
            rect.height = tile->height;
            GetTileSource(&source, tile);
            GetTileOrigin(&origin, tile, size);

            Texture *texture = GetTileImage(tile);
            DrawTexturePro(*texture, source, rect, origin, 0, color);
        }

        ++col;
        if (col >= cols) {
            col = 0;
            ++row;
            rect.x = position.x;
            rect.y += rowh;
        } else {
            rect.x += colw;
        }
    }
}

Sprite* NewTileLayerSprite(tmx_layer *layer, tmx_map *map) {
    Sprite *g = NewSprite();
    if (g) {
        Rectangle rect = {0};
        g->used = true;
        g->rect = rect;
        g->rotationDeg = 0;
        g->color = ColorFromTMX(layer->tintcolor);
        g->behavior.type = SPRITETYPE_TILELAYER;
        g->behavior.update = UpdateSprite_TileLayer;
        g->behavior.draw = DrawSprite_TileLayer;
        g->animSpeedMS = 1000;
        g->layer.layer = layer;
        g->layer.map = map;
    }
    return g;
}