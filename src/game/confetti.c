#include <engine.h>
#include <raylib.h>
#include <math.h>

void Task_Confetti(void *p) {
    Sprite *spr = p;

    spr->animTimer += GetFrameTime();

    spr->size.x = (cosf(spr->animTimer * PI * 8) + 1) * 4;
    spr->origin.x = spr->size.x/2;
    spr->position.y += 8;

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
    rect.width = 8.f ; //* GetRandomValue(1,4);
    rect.height = 8.f; // * GetRandomValue(1,4);
    
    Vector2 origin = {rect.width/2, rect.height/2};
    rect.x = GetRandomValue(origin.x, GetScreenWidth()-origin.x);
    rect.y = 0;

    float rotation = GetRandomValue(0, 89);

    Color color = {
        GetRandomValue(0,255),
        GetRandomValue(0,255),
        GetRandomValue(0,255),
        255
    };

    Sprite *sprite = NewRectangleSprite(rect, origin, rotation, color);
    Task *task = NewTask(Task_Confetti, sprite, 2);
    sprite->exdata = task;
}