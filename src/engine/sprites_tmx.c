#include "gfx2d.h"

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

void GetTileSource(Rectangle *source, tmx_tile *tile, Vector2 flip) {
    source->x  = tile->ul_x;
    source->y  = tile->ul_y;
    source->width  = tile->tileset->tile_width;
    source->height = tile->tileset->tile_height;
    if (flip.x < 0)
        source->width *= -1;
    if (flip.y < 0)
        source->height *= -1;
}

void GetTileOrigin(Vector2 *origin, tmx_tile *tile, Vector2 destSize) {
    tmx_tileset *tileset = tile->tileset;

    Vector2 scale = {1, 1};
    if (destSize.x) scale.x = destSize.x / tileset->tile_width;
    if (destSize.y) scale.y = destSize.y / tileset->tile_height;

    origin->x = scale.x * -tileset->x_offset;
    origin->y = scale.y * (tileset->tile_height - tileset->y_offset);
}

void SetSpriteTile(Sprite *g, tmx_tile *tile, Vector2 flip) {
    Texture *image = GetTileImage(tile);
    if (image == NULL)
        return;

    g->tile.tile = tile;
    g->tile.texture = image;
    GetTileSource(&g->tile.source, tile, flip);
    GetTileOrigin(&g->origin, tile, g->size);

    g->tile.frame = 0;
    g->animTimer = 0;
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
            Vector2 flip = {g->tile.source.width, g->tile.source.height};
            GetTileSource(&g->tile.source, tiles + frame->tile_id, flip);
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
        Vector2 flip = {rect.width, rect.height};
        rect.width = abs(rect.width);
        rect.height = abs(rect.height);
        SetSpriteTile(g, tile, flip);
    }
    return g;
}

Sprite* NewTMXObjectSprite(tmx_object *o, tmx_tile **maptiles, Color color) {
    Rectangle rect = {
        .x = o->x, .y = o->y,
        .width = o->width, .height = o->height
    };

    tmx_template *tmpl = o->template_ref;
    tmx_object *tmplObj = NULL;
    if (tmpl) {
        tmplObj = tmpl->object;
        if (!rect.width)
            rect.width = tmplObj->width;
        if (!rect.height)
            rect.height = tmplObj->height;
    }

    if (o->obj_type == OT_TILE) {
        int gid = o->content.gid;
        tmx_tile *tile = NULL;
        if (gid) {
            int i = gid & TMX_FLIP_BITS_REMOVAL;
            tile = maptiles[i];
        } else if (tmpl && tmpl->tileset_ref) {
            gid = tmplObj->content.gid;
            int i = gid & TMX_FLIP_BITS_REMOVAL;
            tile = tmpl->tileset_ref->tileset->tiles
                + i - tmpl->tileset_ref->firstgid;
        }
        assert(tile);

        rect.width *= (gid & TMX_FLIPPED_HORIZONTALLY) ? -1 : 1;
        rect.height *= (gid & TMX_FLIPPED_VERTICALLY) ? -1 : 1;

        return NewTileSprite(tile, rect, o->rotation, color);
    } else if (o->obj_type == OT_SQUARE) {
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
            Vector2 flip = {
                (gid & TMX_FLIPPED_HORIZONTALLY) ? -1 : 1,
                (gid & TMX_FLIPPED_VERTICALLY) ? -1 : 1
            };
            GetTileSource(&source, tile, flip);
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
        g->animTimer = 0;
        g->animSpeedMS = 1000;
        g->layer.layer = layer;
        g->layer.map = map;
    }
    return g;
}