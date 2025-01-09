#include "gfx2d.h"

#include <assert.h>

#define RAYLIB_ASEPRITE_IMPLEMENTATION
#include <raylib-aseprite.h>

void UpdateSprite(Sprite *spr) {
    if (spr->behavior.update) spr->behavior.update(spr);
}

void DrawSprite(Sprite *spr) {
    if (spr->behavior.draw) spr->behavior.draw(spr);
}

void DrawSprite_Rectangle(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_RECTANGLE);
    DrawRectanglePro(spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

void DrawSprite_Texture(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TEXTURE);
    DrawTexturePro(*spr->texture.texture, spr->texture.source, spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

void DrawSprite_Text(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_TEXT);
    DrawTextBoxed(&spr->text, spr->rect, spr->color);
}

void UpdateSprite_AsepriteTag(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_ASEPRITETAG);
    UpdateAsepriteTag(&spr->asepriteTag);
}

void DrawSprite_AsepriteTag(Sprite *spr) {
    assert(spr->behavior.type == SPRITETYPE_ASEPRITETAG);
    DrawAsepriteTagPro(spr->asepriteTag, spr->rect, spr->origin, spr->rotationDeg, spr->color);
}

pool_ctor(Sprite, SpritePool, NewSpritePool)

SpritePool *sprites;

#define IsActive(g) (g->active)

static void InitEmptySprite(Sprite *spr) {
    spr->active = false;
    spr->behavior.type = SPRITETYPE_NONE;
    spr->behavior.update = spr->behavior.draw = NULL;
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

size_t NumSpritesActive() {
    return sprites->nActive;
}

size_t NumSpritesFree() {
    return count_free_pool_objs(sprites);
}

int SpriteZYXSort(const void *ap, const void *bp) {
    const Sprite *a = *(Sprite**)ap, *b = *(Sprite**)bp;
    float diff;
    diff = a->z - b->z;
    if (diff > 0.0f)
        return 1;
    if (diff < 0.0f)
        return -1;
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
    return a - b;
}

void UpdateSprites() {
    pool_foreachactive(sprites, UpdateSprite);
}

void SortSprites(int (*compare)(const void*,const void*)) {
    sort_pool_active(sprites, compare);
}

void PruneSprites() {
    prune_pool(sprites, IsActive);
}

void DrawSprites() {
    pool_foreachactive(sprites, DrawSprite);
}

Sprite* NewSprite() {
    return take_from_pool(sprites);
}

Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->active = true;
        spr->behavior.type = SPRITETYPE_RECTANGLE;
        spr->behavior.update = NULL;
        spr->behavior.draw = DrawSprite_Rectangle;
        spr->rect = rect;
        spr->origin = origin;
        spr->rotationDeg = rotationDeg;
        spr->color = color;
    }
    return spr;
}

Sprite* NewTextSprite(SpriteText *text, Rectangle rect, Color color) {
    Sprite *spr = NewSprite();
    if (spr) {
        spr->active = true;
        spr->rect = rect;
        spr->origin = (Vector2){0};
        spr->rotationDeg = 0;
        spr->color = color;
        spr->behavior.type = SPRITETYPE_TEXT;
        spr->behavior.update = NULL;
        spr->behavior.draw = DrawSprite_Text;
        spr->text = *text;
    }
    return spr;
}

bool IsNearCamera2D(Vector2 position, Camera2D Camera) {
    float w = GetScreenWidth(), h = GetScreenHeight();
    Vector2 screenCenter = {w/2, h/2};
    Vector2 cameraCenter = GetScreenToWorld2D(screenCenter, currentCamera);
    float nearDist = fmaxf(w, h);
    return Vector2DistanceSqr(position, cameraCenter) <= nearDist*nearDist;
}

void ReleaseSprite(Sprite* spr) {
    spr->active = false;
}