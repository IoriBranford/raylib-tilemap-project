#include <engine/sprites.h>
#include <func.h>
#include <stdlib.h>
#include <assert.h>
#include <util.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

typedef void (*SpriteFunction)(Sprite*);

typedef enum SpriteType {
    SPRITETYPE_NONE,
    SPRITETYPE_RECTANGLE,
    SPRITETYPE_TEXTURE,
    SPRITETYPE_TEXT,
    SPRITETYPE_TILE,
    SPRITETYPE_ASEPRITETAG,
    SPRITETYPE_TYPES
} SpriteType;

typedef struct SpriteBehavior {
    SpriteType type;
    SpriteFunction update, draw;
} SpriteBehavior;

struct Sprite {
    union {
        struct {
            Vector2 position, size;
        };
        Rectangle rect;
    };
    Vector2 origin;
    float rotationDeg;
    Color color;
    bool used;
    unsigned animSpeedMS;

    SpriteBehavior behavior;
    union {
        struct {
            Texture2D *texture;
            Rectangle source;
        } texture;

        struct {
            Font *font;
            const char *text;
            float fontSize;
            float spacing;
        } text;

        struct {
            Texture2D *texture;
            Rectangle source;
            tmx_tile *tile;
            unsigned frame;
            float timer;
            // TODO animation vars
        } tile;

        AsepriteTag asepriteTag;
    };
};

void UpdateSprite(Sprite *g) {
    g->behavior.update(g);
}

void DrawSprite(Sprite *g) {
    g->behavior.draw(g);
}

void DrawSprite_Rectangle(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_RECTANGLE);
    DrawRectanglePro(g->rect, g->origin, g->rotationDeg, g->color);
}

void DrawSprite_Texture(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TEXTURE);
    DrawTexturePro(*g->texture.texture, g->texture.source, g->rect, g->origin, g->rotationDeg, g->color);
}

void DrawSprite_Text(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TEXT);
    DrawTextPro(*g->text.font, g->text.text, g->position, g->origin, g->rotationDeg, g->text.fontSize, g->text.spacing, g->color);
}

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

void UpdateSprite_AsepriteTag(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_ASEPRITETAG);
    UpdateAsepriteTag(&g->asepriteTag);
}

void DrawSprite_AsepriteTag(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_ASEPRITETAG);
    DrawAsepriteTagPro(g->asepriteTag, g->rect, g->origin, g->rotationDeg, g->color);
}

static void Nop(Sprite *_) {}

static const SpriteBehavior BEHAVIORS[SPRITETYPE_TYPES] = {
    [SPRITETYPE_NONE] = {
        .type = SPRITETYPE_NONE,
        .update = Nop,
        .draw = Nop
    },
    [SPRITETYPE_RECTANGLE] = {
        .type = SPRITETYPE_RECTANGLE,
        .update = Nop,
        .draw = DrawSprite_Rectangle
    },
    [SPRITETYPE_TEXTURE] = {
        .type = SPRITETYPE_TEXTURE,
        .update = Nop,
        .draw = DrawSprite_Texture
    },
    [SPRITETYPE_TEXT] = {
        .type = SPRITETYPE_TEXT,
        .update = Nop,
        .draw = DrawSprite_Text
    },
    [SPRITETYPE_TILE] = {
        .type = SPRITETYPE_TILE,
        .update = UpdateSprite_Tile,
        .draw = DrawSprite_Tile
    },
    [SPRITETYPE_ASEPRITETAG] = {
        .type = SPRITETYPE_ASEPRITETAG,
        .update = UpdateSprite_AsepriteTag,
        .draw = DrawSprite_AsepriteTag
    }
};

pool_typedef(Sprite, SpritePool)
pool_ctor(Sprite, SpritePool, NewSpritePool)

static SpritePool *sprites;

#define IsUsed(g) (g->used)

static void InitEmptySprite(Sprite *sprite) {
    sprite->used = false;
    sprite->behavior = BEHAVIORS[SPRITETYPE_NONE];
}

void InitSprites(unsigned n) {
    if (sprites)
        CloseSprites();
    sprites = NewSpritePool(n);
    pool_foreachall(sprites, InitEmptySprite);
}

void CloseSprites() {
    if (sprites)
        free_pool(sprites);
    sprites = NULL;
}

size_t NumSpritesAvailable() {
    return count_free_pool_objs(sprites);
}

int CompareSprites(const void *ap, const void *bp) {
    const Sprite *a = ap, *b = bp;
    float diff;
    // float diff = a->order - b->order;
    // if (diff > 0.0f)
    //     return 1;
    // if (diff < 0.0f)
    //     return -1;
    diff = a->position.y - b->position.y;
    if (diff > 0.0f)
        return 1;
    if (diff < 0.0f)
        return -1;
    diff = a->position.x - b->position.x;
    if (diff > 0.0f)
        return 1;
    if (diff < 0.0f)
        return -1;
    return 0;
}

void UpdateSprites() {
    pool_foreachused(sprites, UpdateSprite);
    sort_pool_used(sprites, CompareSprites);
}

void PruneSprites() {
    prune_pool(sprites, IsUsed);
}

void DrawSprites() {
    pool_foreachused(sprites, DrawSprite);
}

Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color) {
    Sprite *g = take_from_pool(sprites);
    if (g) {
        g->used = true;
        g->behavior = BEHAVIORS[SPRITETYPE_RECTANGLE];
        g->rect = rect;
        g->origin = origin;
        g->rotationDeg = rotationDeg;
        g->color = color;
    }
    return g;
}

Sprite* NewTileSprite(tmx_tile *tile, Rectangle rect, float rotationDeg, Color color) {
    Sprite *g = take_from_pool(sprites);
    if (g) {
        g->used = true;
        g->rect = rect;
        g->rotationDeg = rotationDeg;
        g->color = color;
        g->behavior = BEHAVIORS[SPRITETYPE_TILE];
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
    }

    return NULL;
}

void ReleaseSprite(Sprite* sprite) {
    sprite->used = false;
}