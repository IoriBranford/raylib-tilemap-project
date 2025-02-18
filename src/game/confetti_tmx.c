#include <engine.h>
#include <game.h>
#include <raylib.h>
#include <math.h>

void Task_TMXObjectConfetti(Task *t) {
    cpBody *body = t->data;
    Sprite *spr = cpBodyGetUserData(body);

    UpdateSpriteFromBody(body, spr);
    if (!CheckCollisionRecs(spr->rect,
    (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()})) {
        ReleaseTask(t);
        ReleaseBody(body);
        ReleaseSprite(spr);
        return;
    }

    cpFloat mass = cpBodyGetMass(body);
    cpBodySetForce(body, cpv(0, -mass/64));

    float sinAngleRad = sinf(GetTime() * PI * 4);
    spr->size.x = (sinAngleRad + 1) * spr->size.y / 2;
    spr->origin.x = spr->size.x/2;

    Color color = spr->color;
    unsigned sat = (sinAngleRad + 1) * 256 / 2;
    if (sat > 255) sat = 255;
    else if (sat < 1) sat = 1;
    if (color.r) color.r = sat;
    if (color.g) color.g = sat;
    if (color.b) color.b = sat;
    spr->color = color;
}

void DrawTMXTileCollisionShapes(tmx_tile *tile, Vector2 position, float rotationDeg, Color color);

void DrawSprite_ConfettiWithCollision(Sprite *spr) {
    DrawTexturePro(spr->tile.texture, spr->tile.source, spr->rect, spr->origin, spr->rotationDeg, spr->color);
    DrawRectangle(spr->x - 1, spr->y - 4, 2, 8, WHITE);
    DrawRectangle(spr->x - 4, spr->y - 1, 8, 2, WHITE);
    DrawTMXTileCollisionShapes(spr->tile.tile, spr->position, spr->rotationDeg, WHITE);
}

void AddTMXObjectConfetti(tmx_object *obj, tmx_map *map) {
    if (!NumSpritesFree() || !NumTasksFree())
        return;

    cpVect pos = {GetRandomValue(0, GetScreenWidth()), 0};

    float rotation = GetRandomValue(0, 89);

    Color color = ColorFromHSV(GetRandomValue(0,5) * 60, 1, 1);

    cpBody *body = AddNewTMXObjectBody(obj, map);
    cpBodySetPosition(body, pos);
    cpBodySetVelocity(body, cpv(0,4));
    cpBodySetAngularVelocity(body, PI/16);

    Sprite *sprite = NewTMXObjectSprite(obj, map, color);
    sprite->behavior.draw = DrawSprite_ConfettiWithCollision;
    cpBodySetUserData(body, sprite);
    UpdateSpriteFromBody(body, sprite);
    Task *task = NewTask(Task_TMXObjectConfetti, body, 2);
}