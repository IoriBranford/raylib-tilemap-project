#include <engine.h>
#include <game.h>
#include <raylib.h>
#include <math.h>

void Task_Confetti(Task *t) {
    cpBody *body = t->data;
    Sprite *spr = cpBodyGetUserData(body);

    UpdateSpriteFromBody(body, spr);
    if (!CheckCollisionRecs(spr->rect,
    (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()})) {
        ReleaseTask(t);
        cpBodyDestroy(body);
        ReleaseSprite(spr);
        return;
    }

    cpFloat mass = cpBodyGetMass(body);
    cpBodySetForce(body, cpv(0, -mass/64));

    spr->animTimer += GetFrameTime();

    float sinAngleRad = sinf(spr->animTimer * PI * 4);
    spr->size.x = (sinAngleRad + 1) * 8 / 2;
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

void AddConfetti() {
    if (!NumSpritesFree() || !NumTasksFree())
        return;

    Rectangle rect;
    rect.width = 0;
    rect.height = 8;
    
    Vector2 origin = {rect.width/2, rect.height/2};
    rect.x = GetRandomValue(origin.x, GetScreenWidth()-origin.x);
    rect.y = 0;

    float rotation = GetRandomValue(0, 89);

    Color color = ColorFromHSV(GetRandomValue(0,5) * 60, 1, 1);

    cpBody *body = NewBody(rect.x, rect.y, rotation * DEG2RAD);
    cpBodySetVelocity(body, cpv(0,4));
    cpBodySetAngularVelocity(body, PI/16);
    AddBodyCircle(body, 1, 0, 0);

    Sprite *sprite = NewRectangleSprite(rect, origin, rotation, color);
    sprite->animTimer = 0;
    cpBodySetUserData(body, sprite);

    Task *task = NewTask(Task_Confetti, body, 2);
}