#include <engine.h>
#include <raylib.h>
#include <math.h>

void Task_Confetti(void *p) {
    Sprite *spr = p;

    spr->animTimer += 1;

    float sinAngleRad = sinf(spr->animTimer * PI * 4 / 60);
    spr->size.x = (sinAngleRad + 1) * 8 / 2;
    spr->origin.x = spr->size.x/2;
    spr->position.y += 2;

    Color color = spr->color;
    unsigned sat = (sinAngleRad + 1) * 256 / 2;
    if (sat > 255) sat = 255;
    else if (sat < 1) sat = 1;
    if (color.r) color.r = sat;
    if (color.g) color.g = sat;
    if (color.b) color.b = sat;
    spr->color = color;

    if (spr->position.y >= GetScreenHeight() + spr->size.y) {
        Task *t = spr->exdata;
        EndTask(t);
        ReleaseSprite(spr);
    }
}

void AddConfetti() {
    if (!NumSpritesAvailable() || !NumTasksAvailable())
        return;

    Rectangle rect;
    rect.width = 0;
    rect.height = 8;
    
    Vector2 origin = {rect.width/2, rect.height/2};
    rect.x = GetRandomValue(origin.x, GetScreenWidth()-origin.x);
    rect.y = 0;

    float rotation = GetRandomValue(0, 89);

    Color color = ColorFromHSV(GetRandomValue(0,5) * 60, 1, 1);

    Sprite *sprite = NewRectangleSprite(rect, origin, rotation, color);
    Task *task = NewTask(Task_Confetti, sprite, 2);
    sprite->exdata = task;
    sprite->animTimer = 0;
}