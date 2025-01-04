#include <game.h>
#include <engine.h>
#include <raylib.h>
#include <string.h>
#include <stdio.h>

void UpdateLogo();
void DrawLogo();
void UpdateTitle();
void DrawTitle();
void UpdateGameplay();
void DrawGameplay();
void UpdateEnding();
void DrawEnding();

void AddConfetti();

const Phase LogoPhase = {
    .update = UpdateLogo,
    .draw = DrawLogo
};
const Phase TitlePhase = {
    .update = UpdateTitle,
    .draw = DrawTitle
};
const Phase GameplayPhase = {
    .update = UpdateGameplay,
    .draw = DrawGameplay
};
const Phase EndingPhase = {
    .update = UpdateEnding,
    .draw = DrawEnding
};

static int framesCounter = 0;          // Useful to count frames
#define FRAMES_PER_CONFETTI 1
#define MAX_CONFETTI 1000

static tmx_map *map;
static Camera2D camera;

void InitGame()
{
    map = LoadMap("resources/desert.tmx");
    SetCurrentPhase(LogoPhase);
    InitTasks(256);
    InitLua();
    RunLua("resources/syntaxerr.lua");
    RunLua("resources/runtimeerr.lua");
    RunLua("resources/hello.lua");
}

void CloseGame()
{
    UnloadMap(map);
}

void InitLayers(tmx_layer *head, tmx_map *map) {
    for (tmx_layer *layer = head; layer; layer = layer->next) {
        if (layer->type == L_GROUP) {
            InitLayers(layer->content.group_head, map);
        } else if (layer->type == L_OBJGR) {
            for (tmx_object *o = layer->content.objgr->head; o; o = o->next)
                NewTMXObjectSprite(o, map->tiles, WHITE);
        } else if (layer->type == L_LAYER) {
            NewTileLayerSprite(layer, map);
        }
    }
}

void Task_SpawnConfetti(void *p) {
    if (framesCounter == 0) {
        AddConfetti();
    }
    ++framesCounter;
    framesCounter %= FRAMES_PER_CONFETTI;
}

void UpdateLogo()
{
    // TODO: Update LOGO screen variables here!
    UpdateTasks();

    framesCounter++;    // Count frames

    // Wait for 2 seconds (120 frames) before jumping to TITLE screen
    if (framesCounter > 120)
    {
        CloseLua();
        CloseTasks();
        SetCurrentPhase(TitlePhase);
    }
}

void UpdateTitle()
{
    // Press enter to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        InitSprites(MAX_CONFETTI);
        InitLayers(map->ly_head, map);
        camera.offset.x = GetScreenWidth()/2;
        camera.offset.y = GetScreenHeight()/2;
        camera.target = camera.offset;
        camera.rotation = 0;
        camera.zoom = 1;
        SetCurrentPhase(GameplayPhase);
    }
}

void UpdateGameplay()
{
    UpdateSprites();

    if (IsMouseButtonDown(0)) {
        Vector2 move = GetMouseDelta();
        camera.target.x -= move.x;
        camera.target.y -= move.y;
    }

    // Press enter to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        InitPhysics(64);
        InitSprites(MAX_CONFETTI);
        InitTasks(MAX_CONFETTI);
        SetCurrentPhase(EndingPhase);
    }
}

void UpdateEnding()
{
    UpdatePhysics();
    UpdateSprites();
    UpdateTasks();

    if (framesCounter == 0) {
        AddConfetti();
    }
    ++framesCounter;
    framesCounter %= FRAMES_PER_CONFETTI;
    
    PruneSprites();

    // Press enter to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        ClosePhysics();
        CloseSprites();
        CloseTasks();
        SetCurrentPhase(TitlePhase);
    }
}

void DrawLogo()
{
    // TODO: Draw LOGO screen here!
    DrawText("LOGO SCREEN", 0, 0, 40, LIGHTGRAY);
    DrawText("WAIT for 2 SECONDS...", 0, 40, 20, GRAY);
}

void DrawTitle()
{
    // TODO: Draw TITLE screen here!
    ClearBackground(GREEN);
    DrawText("TITLE SCREEN", 0, 0, 40, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 0, 40, 20, DARKGREEN);
}

void DrawGameplay()
{
    // TODO: Draw GAMEPLAY screen here!
    ClearBackground(tmx2rl_Color(map->backgroundcolor));
    BeginMode2D(camera);
    DrawSprites();
    EndMode2D();
    DrawText("GAMEPLAY SCREEN", 0, 0, 40, MAROON);
    DrawText("PRESS ENTER to JUMP to ENDING SCREEN", 0, 40, 20, MAROON);
}

void DrawEnding()
{
    ClearBackground(BLACK);
    DrawSprites();
    DrawText("ENDING SCREEN", 0, 0, 40, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 0, 40, 20, DARKBLUE);
    char s[256];
    sprintf(s, "sprites %4d", NumSpritesActive());
    DrawText(s, 0, 80, 20, DARKGREEN);
    sprintf(s, "tasks %4d", NumTasksActive());
    DrawText(s, 0, 100, 20, DARKGREEN);
}