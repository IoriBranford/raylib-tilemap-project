#include <engine/sprites.h>
#include <func.h>
#include <stdlib.h>
#include <assert.h>
#include <util.h>

#include <raylib-tmx.h>

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

    SpriteBehavior behavior;
    union {
        struct {
            Texture2D texture;
            Rectangle source;
        } texture;

        struct {
            Font font;
            const char *text;
            float fontSize;
            float spacing;
        } text;

        struct {
            tmx_tile *tile;
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
    DrawTexturePro(g->texture.texture, g->texture.source, g->rect, g->origin, g->rotationDeg, g->color);
}

void DrawSprite_Text(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TEXT);
    DrawTextPro(g->text.font, g->text.text, g->position, g->origin, g->rotationDeg, g->text.fontSize, g->text.spacing, g->color);
}

void DrawSprite_Tile(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_TILE);
    DrawTMXTilePro(g->tile.tile, g->rect, g->rotationDeg, g->color);
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
        .update = Nop,
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

void InitSprites(unsigned n) {
    sprites = NewSpritePool(n);
}

void CloseSprites() {
    free_pool(sprites);
    sprites = NULL;
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
    prune_pool(sprites, IsUsed);
    pool_foreachused(sprites, UpdateSprite);
    sort_pool_used(sprites, CompareSprites);
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