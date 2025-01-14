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
void AddTMXObjectConfetti(tmx_object *obj, tmx_tile **maptiles);

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
static Sprite *camera;
static int luaTasks[2] = {LUA_REFNIL, LUA_REFNIL};

void InitGame()
{
    map = LoadMap("resources/desert.tmx");
    SetCurrentPhase(LogoPhase);
    InitTasks(256);
    InitLua();
    // RunLua("resources/syntaxerr.lua", 0);
    // RunLua("resources/runtimeerr.lua", 0);
    luaTasks[0] = RunLua("resources/hello.lua", 0, "ii", 2, 30);
    luaTasks[1] = RunLua("resources/hello.lua", 0, "ii", 3, 30);
}

void CloseGame()
{
    UnloadMap(map);
}

void InitLayers(tmx_layer *head, tmx_map *map) {
    float z = 0;
    for (tmx_layer *layer = head; layer; layer = layer->next) {
        if (layer->type == L_GROUP) {
            InitLayers(layer->content.group_head, map);
        } else if (layer->type == L_OBJGR) {
            z += 1;
            for (tmx_object *o = layer->content.objgr->head; o; o = o->next) {
                Sprite *s = NewTMXObjectSprite(o, map->tiles, WHITE);
                if (s)
                    s->z = z;
            }
        } else if (layer->type == L_LAYER) {
            Sprite *s = NewTileLayerSprite(layer, map);
            s->z = z += 1;
        }
    }
}

void Task_SpawnConfetti(void *p) {
    if (framesCounter == 0) {
        AddTMXObjectConfetti(tmx_find_object_by_id(map, 16), map->tiles);
    }
    ++framesCounter;
    framesCounter %= FRAMES_PER_CONFETTI;
}

void UpdateLogo()
{
    // TODO: Update LOGO screen variables here!
    UpdateTasks();

    for (int i = 0; i < 2; ++i) {
        Task *t = GetLuaTask(luaTasks[i]);
        if (t) {
            if (IsTaskDone(t)) {
                const char *result = LuaResultString(luaTasks[i], 1);
                printf("%s\n", result);
                UnrefLuaTask(luaTasks[i]);
                luaTasks[i] = LUA_REFNIL;
            }
        }
    }

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
        camera = NewSpriteCamera((Camera2D){0}, WHITE);
        camera->z = 0x10000;
        camera = NewSpriteCamera((Camera2D){
            .offset.x = GetScreenWidth()/2,
            .offset.y = GetScreenHeight()/2,
            .target.x = GetScreenWidth()/2,
            .target.y = GetScreenHeight()/2,
            .rotation = 0,
            .zoom = 1
        }, WHITE);
        camera->z = -0x10000;
        SetCurrentPhase(GameplayPhase);
    }
}

void UpdateGameplay()
{
    UpdateSprites();

    if (IsMouseButtonDown(0)) {
        Vector2 move = GetMouseDelta();
        camera->x -= move.x;
        camera->y -= move.y;
    }

    // Press enter to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        framesCounter = 0;
        InitPhysics();
        InitSprites(MAX_CONFETTI);
        InitTasks(MAX_CONFETTI);
        InitLua();
        SetCurrentPhase(EndingPhase);
    }
}

void UpdateEnding()
{
    UpdatePhysics();
    UpdateSprites();
    UpdateTasks();
    UpdateLua();

    if (framesCounter == 0) {
        UnrefLuaTask(RunLua("resources/confetti.lua", 0, NULL));
        // AddTMXObjectConfetti(tmx_find_object_by_id(map, 16), map->tiles);
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
        CloseLua();
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
    SortSprites(SpriteZYXSort);
    DrawSprites();
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