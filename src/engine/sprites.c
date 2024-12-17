#include "sprites.h"

#include <assert.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

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

void UpdateSprite_AsepriteTag(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_ASEPRITETAG);
    UpdateAsepriteTag(&g->asepriteTag);
}

void DrawSprite_AsepriteTag(Sprite *g) {
    assert(g->behavior.type == SPRITETYPE_ASEPRITETAG);
    DrawAsepriteTagPro(g->asepriteTag, g->rect, g->origin, g->rotationDeg, g->color);
}

static void Nop(Sprite *_) {}

const SpriteBehavior BEHAVIORS[SPRITETYPE_TYPES] = {
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
    [SPRITETYPE_ASEPRITETAG] = {
        .type = SPRITETYPE_ASEPRITETAG,
        .update = UpdateSprite_AsepriteTag,
        .draw = DrawSprite_AsepriteTag
    }
};

pool_ctor(Sprite, SpritePool, NewSpritePool)

SpritePool *sprites;

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
}

void SortSprites(int (*compare)(const void*,const void*)) {
    sort_pool_used(sprites, compare);
}

void PruneSprites() {
    prune_pool(sprites, IsUsed);
}

void DrawSprites() {
    pool_foreachused(sprites, DrawSprite);
}

Sprite* NewSprite() {
    return take_from_pool(sprites);
}

Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color) {
    Sprite *g = NewSprite();
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

void ReleaseSprite(Sprite* sprite) {
    sprite->used = false;
}