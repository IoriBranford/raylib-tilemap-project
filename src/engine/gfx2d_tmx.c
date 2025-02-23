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

static const Vector2 ALIGNMENT_ORIGIN[] = {
    [OA_NONE]       = {0.0f, 1.0f},
    [OA_TOPLEFT]    = {0.0f, 0.0f},
    [OA_TOP]        = {0.5f, 0.0f},
    [OA_TOPRIGHT]   = {1.0f, 0.0f},
    [OA_LEFT]       = {0.0f, 0.5f},
    [OA_CENTER]     = {0.5f, 0.5f},
    [OA_RIGHT]      = {1.0f, 0.5f},
    [OA_BOTTOMLEFT] = {0.0f, 1.0f},
    [OA_BOTTOM]     = {0.5f, 1.0f},
    [OA_BOTTOMRIGHT]= {1.0f, 1.0f},
};

void GetTileOrigin(Vector2 *origin, tmx_tile *tile, Vector2 destSize) {
    tmx_tileset *tileset = tile->tileset;

    *origin = ALIGNMENT_ORIGIN[tileset->objectalignment];
    origin->x *= tileset->tile_width;
    origin->y *= tileset->tile_height;
    origin->x -= tileset->x_offset;
    origin->y -= tileset->y_offset;

    if (destSize.x) origin->x *= destSize.x / tileset->tile_width;
    if (destSize.y) origin->y *= destSize.y / tileset->tile_height;
}

tmx_tile* GetSpriteTile(Sprite *spr) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return NULL;
    return spr->tile.tile;
}

tmx_tileset* GetSpriteTileset(Sprite *spr) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return NULL;
    return spr->tile.tile->tileset;
}

tmx_tile* GetTilesetNamedTile(tmx_tileset *tileset, const char *name) {
    tmx_property *prop = tmx_get_property(tileset->properties, name);
    if (!prop || prop->type != PT_INT)
        return NULL;
    int tid = prop->value.integer;
    if (tid < 0 || tid >= tileset->tilecount)
        return NULL;
    return tileset->tiles + tid;
}

void SetSpriteTile(Sprite *spr, tmx_tile *tile) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return;

    Texture *image = GetTileImage(tile);
    if (image == NULL)
        return;

    spr->tile.tile = tile;
    spr->tile.texture = *image;
    Vector2 flip = {spr->tile.source.width, spr->tile.source.height};
    GetTileSource(&spr->tile.source, tile, flip);
    GetTileOrigin(&spr->origin, tile, spr->size);

    spr->tile.frame = 0;
    spr->animTimer = 0;
}

void SetSpriteTileFlipX(Sprite *spr, float flip) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return;
    spr->tile.source.width = fabsf(spr->tile.source.width);
    if (flip < 0)
        spr->tile.source.width *= -1;
}

void SetSpriteTileFlipY(Sprite *spr, float flip) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return;
    spr->tile.source.height = fabsf(spr->tile.source.height);
    if (flip < 0)
        spr->tile.source.height *= -1;
}

void SetSpriteTileFlip(Sprite *spr, Vector2 flip) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return;
    spr->tile.source.width = fabsf(spr->tile.source.width);
    if (flip.x < 0)
        spr->tile.source.width *= -1;
    spr->tile.source.height = fabsf(spr->tile.source.height);
    if (flip.y < 0)
        spr->tile.source.height *= -1;
}

void SetSpriteTileIfNew(Sprite *spr, tmx_tile *tile) {
    if (tile != spr->tile.tile)
        SetSpriteTile(spr, tile);
}

tmx_tile* SetSpriteNamedTileFromCurrentTileset(Sprite *spr, const char *name) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return NULL;
    tmx_tile *tile = GetTilesetNamedTile(spr->tile.tile->tileset, name);
    if (tile)
        SetSpriteTile(spr, tile);
    return tile;
}

tmx_tile* SetSpriteNamedTileFromCurrentTilesetIfNew(Sprite *spr, const char *name) {
    if (spr->behavior.type != SPRITETYPE_TILE)
        return NULL;
    tmx_tile *tile = GetTilesetNamedTile(spr->tile.tile->tileset, name);
    if (tile && tile != spr->tile.tile)
        SetSpriteTile(spr, tile);
    return tile;
}

void UpdateSprite_Tile(Sprite *spr) {
    tmx_tile *tile = spr->tile.tile;
    tmx_anim_frame *anim = tile->animation;
    unsigned n = tile->animation_len;
    if (anim && n) {
        tmx_tile *tiles = tile->tileset->tiles;
        tmx_anim_frame *frame = anim + spr->tile.frame;

        spr->animTimer += GetFrameTime()*spr->animSpeedMS;

        while (spr->animTimer >= frame->duration) {
            spr->animTimer -= frame->duration;
            ++spr->tile.frame;
            spr->tile.frame %= n;
            frame = anim + spr->tile.frame;
            Vector2 flip = {spr->tile.source.width, spr->tile.source.height};
            GetTileSource(&spr->tile.source, tiles + frame->tile_id, flip);
        }
    }
}

void DrawSprite_Tile(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TILE);
    DrawTexturePro(spr->tile.texture, spr->tile.source, spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

Sprite* NewTileSprite(tmx_tile *tile, Rectangle rect, float rotationDeg, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->active = true;
        spr->rect = rect;
        spr->rotationDeg = rotationDeg;
        spr->color = color;
        spr->behavior.type = SPRITETYPE_TILE;
        spr->behavior.update = UpdateSprite_Tile;
        spr->behavior.draw = DrawSprite_Tile;
        spr->animSpeedMS = 1000;
        Vector2 flip = {rect.width, rect.height};
        rect.width = fabsf(rect.width);
        rect.height = fabsf(rect.height);
        SetSpriteTile(spr, tile);
        SetSpriteTileFlip(spr, flip);
    }
    return spr;
}

void DrawSprite_Shape(Sprite *spr) {
    int n = spr->shape.points_len;
    double **points = spr->shape.points;
    float x0 = spr->position.x, y0 = spr->position.y;

    for (int i = 1; i < n; i++) {
		DrawLineEx((Vector2){x0 + points[i-1][0], y0 + points[i-1][1]},
		           (Vector2){x0 + points[i][0],   y0 + points[i][1]},
		           spr->shape.thick, spr->color);
	}

    if (spr->shape.closed) {
        DrawLineEx((Vector2){(float)(x0 + points[0][0]),    (float)(y0 + points[0][1])},
		           (Vector2){(float)(x0 + points[n-1][0]),  (float)(y0 + points[n-1][1])},
		           spr->shape.thick, spr->color);
    }
}

Sprite* NewShapeSprite(tmx_shape *shape, float thick, bool closed, Vector2 position, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->active = true;
        spr->position = position;
        spr->rotationDeg = 0;
        spr->color = color;
        spr->behavior.type = SPRITETYPE_SHAPE;
        spr->behavior.update = NULL;
        spr->behavior.draw = DrawSprite_Shape;
        spr->shape.points = shape->points;
        spr->shape.points_len = shape->points_len;
        spr->shape.thick = thick;
        spr->shape.closed = closed;
    }
    return spr;
}

tmx_tile* GetTMXObjectTile(tmx_object *o, tmx_map *map) {
    if (o->obj_type != OT_TILE)
        return NULL;
    int gid = o->content.gid;
    tmx_tile *tile = NULL;
    if (gid) {
        int i = gid & TMX_FLIP_BITS_REMOVAL;
        tile = map->tiles[i];
    } else {
        tmx_template *tmpl = o->template_ref;
        if (tmpl && tmpl->tileset_ref) {
            gid = tmpl->object->content.gid;
            int i = gid & TMX_FLIP_BITS_REMOVAL;
            tile = tmpl->tileset_ref->tileset->tiles
                + i - tmpl->tileset_ref->firstgid;
        }
    }
    return tile;
}

Sprite* NewTMXObjectSprite(tmx_object *o, tmx_map *map, Color color) {
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
        tmx_tile *tile = GetTMXObjectTile(o, map);
        assert(tile);

        rect.width *= (gid & TMX_FLIPPED_HORIZONTALLY) ? -1 : 1;
        rect.height *= (gid & TMX_FLIPPED_VERTICALLY) ? -1 : 1;

        return NewTileSprite(tile, rect, o->rotation, color);
    } else if (o->obj_type == OT_SQUARE) {
        Vector2 origin = { 0, 0 };
        return NewRectangleSprite(rect, origin, o->rotation, color);
    } else if (o->obj_type == OT_POLYLINE) {
        return NewShapeSprite(o->content.shape, 1, false, (Vector2){o->x, o->y}, color);
    } else if (o->obj_type == OT_POLYGON) {
        return NewShapeSprite(o->content.shape, 1, true, (Vector2){o->x, o->y}, color);
    } else if (o->obj_type == OT_TEXT) {
        static const float HALIGN[] = {
            [HA_NONE] = 0,
            [HA_LEFT] = 0,
            [HA_CENTER] = 0.5f,
            [HA_RIGHT] = 1,
            [HA_JUSTIFY] = 0
        };
        static const float VALIGN[] = {
            [VA_NONE] = 0,
            [VA_TOP] = 0,
            [VA_CENTER] = 0.5f,
            [VA_BOTTOM] = 1,
        };

        tmx_text *tmxText = o->content.text;
        if (!tmxText && tmpl) {
            tmxText = tmpl->object->content.text;
        }
        assert(tmxText);

        SpriteText text = {
            .font = *(Font*)tmxText->resource_font,
            .fontSize = tmxText->pixelsize,
            .text = tmxText->text,
            .wrap = tmxText->wrap != 0,
            .halign = HALIGN[tmxText->halign],
            .valign = VALIGN[tmxText->valign]
        };
        text.spacing = floorf(text.fontSize / text.font.baseSize);

        Color textColor = tmx2rl_Color(tmxText->color);
        if (ColorIsEqual(textColor, BLANK))
            textColor = BLACK;
        color = ColorTint(textColor, color);

        return NewTextSprite(&text, rect, color);
    }

    return NULL;
}

void SetLayerSpriteSource(Sprite *spr, Rectangle source) {
    assert(spr->behavior.type == SPRITETYPE_TILELAYER);
    tmx_map *map = spr->layer.map;
    tmx_layer *layer = spr->layer.layer;
    if (source.x < 0) source.x = 0;
    if (source.y < 0) source.y = 0;
    if (source.width > map->width - source.x)
        source.width = map->width - source.x;
    else if (source.width == 0)
        source.width = map->width;
    if (source.height > map->height - source.y)
        source.height = map->height - source.y;
    else if (source.height == 0)
        source.height = map->height;
    spr->layer.source = source;
}

void UpdateSprite_TileLayer(Sprite *spr) {
    spr->animTimer += GetFrameTime()*spr->animSpeedMS;
}

void DrawSprite_TileLayer(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TILELAYER);
    tmx_map *map = spr->layer.map;
    tmx_layer *layer = spr->layer.layer;

    assert(layer->type == L_LAYER);

    uint32_t *gids = layer->content.gids;
    tmx_tile **mapTiles = map->tiles;
    
    int col = spr->layer.source.x;
    int row = spr->layer.source.y;
    int cols = spr->layer.source.width;
    int rows = spr->layer.source.height;
    int row2 = row + rows;
    int colw = map->tile_width;
    int rowh = map->tile_height;
    int n = cols * rows;

    Rectangle tileSource;
    Vector2 position = {
        .x = spr->position.x,
        .y = spr->position.y + rowh
    };
    float x0 = position.x;
    Color color = tmx2rl_Color(layer->tintcolor);

    for (; row < row2; ++row, position.x = x0, position.y += rowh) {
        int i = row*map->width + col;
        int i2 = i + cols;
        for (; i < i2; ++i, position.x += colw) {
            uint32_t gid = gids[i];
            uint32_t tileId = gid & TMX_FLIP_BITS_REMOVAL;
            if (!tileId)
                continue;

            tmx_tile *tile = mapTiles[tileId];

            tmx_anim_frame *anim = tile->animation;
            if (anim) {
                float totalDuration = 0;
                for (unsigned i = 0; i < tile->animation_len; ++i)
                    totalDuration += anim[i].duration;

                float animTime = fmodf(spr->animTimer, totalDuration);

                for (unsigned i = 0; i < tile->animation_len; ++i) {
                    if (animTime < anim[i].duration) {
                        tile = tile->tileset->tiles + anim[i].tile_id;
                        break;
                    }
                    animTime -= anim[i].duration;
                }
            }

            Vector2 origin = { tile->width / 2, tile->height / 2 };
            Rectangle rect = {
                position.x + origin.x + tile->tileset->x_offset,
                position.y - origin.y + tile->tileset->y_offset,
                tile->width,
                tile->height
            };
            Vector2 flip = {
                (gid & TMX_FLIPPED_HORIZONTALLY) ? -1 : 1,
                (gid & TMX_FLIPPED_VERTICALLY) ? -1 : 1
            };
            GetTileSource(&tileSource, tile, flip);

            Texture *texture = GetTileImage(tile);
            DrawTexturePro(*texture, tileSource, rect, origin, 0, color);
        }
    }
}

Sprite* NewTileLayerSprite(tmx_layer *layer, tmx_map *map, Rectangle source, Rectangle rect) {
    if (layer->type != L_LAYER) return NULL;
    Sprite *spr = NewSprite();
    if (spr) {
        spr->active = true;
        spr->rect = rect;
        spr->rotationDeg = 0;
        spr->color = tmx2rl_Color(layer->tintcolor);
        spr->behavior.type = SPRITETYPE_TILELAYER;
        spr->behavior.update = UpdateSprite_TileLayer;
        spr->behavior.draw = DrawSprite_TileLayer;
        spr->animTimer = 0;
        spr->animSpeedMS = 1000;
        spr->layer.layer = layer;
        spr->layer.map = map;
        SetLayerSpriteSource(spr, source);
    }
    return spr;
}

Sprite* NewImageLayerSprite(tmx_layer *layer) {
    if (layer->type != L_IMAGE) return NULL;
    Texture2D* texture = layer->content.image->resource_image;
    return NewTextureSprite(
        *texture,
        (Rectangle){0},
        (Rectangle){
            layer->offsetx, layer->offsety,
            texture->width, texture->height
        },
        (Vector2){0},
        0,
        tmx2rl_Color(layer->tintcolor));
}