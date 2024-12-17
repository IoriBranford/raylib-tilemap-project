#include "sprites.h"

#include <assert.h>

void SetTileSpriteSource(Sprite *g, tmx_tile *tile) {
    g->tile.source.x  = tile->ul_x;
    g->tile.source.y  = tile->ul_y;
    g->tile.source.width  = tile->tileset->tile_width;
    g->tile.source.height = tile->tileset->tile_height;
}

void SetSpriteTile(Sprite *g, tmx_tile *tile) {
    g->tile.tile = tile;

    Texture* image = NULL;
    tmx_tileset *tileset = tile->tileset;

    tmx_image *im = tile->image;
    if (im && im->resource_image) {
        image = (Texture*)im->resource_image;
    }
    else if (tile->tileset->image->resource_image) {
        image = (Texture*)tileset->image->resource_image;
    }
    g->tile.texture = image;

    if (image == NULL)
        return;

    SetTileSpriteSource(g, tile);
    
    if (g->rect.width == 0.0f)
        g->rect.width = g->tile.source.width;
    if (g->rect.height == 0.0f)
        g->rect.height = g->tile.source.height;

    g->origin.x = -(float)tileset->x_offset
        * g->rect.width / g->tile.source.width;
    g->origin.y = (g->tile.source.height - tileset->y_offset)
        * g->rect.height / g->tile.source.height;

    g->tile.frame = 0;
}

void UpdateSprite_Tile(Sprite *g) {
    tmx_tile *tile = g->tile.tile;
    tmx_anim_frame *anim = tile->animation;
    unsigned n = tile->animation_len;
    if (anim && n) {
        tmx_tile *tiles = tile->tileset->tiles;
        tmx_anim_frame *frame = anim + g->tile.frame;

        g->tile.timer += GetFrameTime()*g->animSpeedMS;

        while (g->tile.timer >= frame->duration) {
            g->tile.timer -= frame->duration;
            ++g->tile.frame;
            g->tile.frame %= n;
            frame = anim + g->tile.frame;
            SetTileSpriteSource(g, tiles + frame->tile_id);
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