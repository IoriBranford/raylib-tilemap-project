#include <game.h>
#include <engine.h>
#include <raylib.h>
#include <string.h>

void UpdateLogo();
void DrawLogo();
void UpdateTitle();
void DrawTitle();
void UpdateGameplay();
void DrawGameplay();
void UpdateEnding();
void DrawEnding();

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
#define FRAMES_PER_SPRITE 10
#define MAX_SPRITES 100

static int spriteIndex = 0;
static Sprite *sprites[MAX_SPRITES];
static tmx_map *map;
static Camera2D camera;

void InitGame()
{
    map = LoadTMX("resources/desert.tmx");
    SetCurrentPhase(LogoPhase);
}

void CloseGame()
{
    UnloadTMX(map);
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

Sprite* GenRandomRect() {
    Rectangle rect;
    rect.width = 8.f * GetRandomValue(1,4);
    rect.height = 8.f * GetRandomValue(1,4);
    
    Vector2 origin = {rect.width/2, rect.height/2};
    rect.x = GetRandomValue(origin.x, 480*2-origin.x);
    rect.y = GetRandomValue(origin.y, 270*2-origin.y);

    float rotation = GetRandomValue(0, 179);

    Color color = {
        GetRandomValue(0,255),
        GetRandomValue(0,255),
        GetRandomValue(0,255),
        255
    };

    return NewRectangleSprite(rect, origin, rotation, color);
}

void UpdateRandomRects() {
    if (!NumSpritesAvailable()) {
        ReleaseSprite(sprites[spriteIndex]);
    }

    PruneSprites();
    UpdateSprites();

    if (framesCounter == 0) {
        sprites[spriteIndex++] = GenRandomRect();
        spriteIndex %= MAX_SPRITES;
    }
    ++framesCounter;
    framesCounter %= FRAMES_PER_SPRITE;
}

void UpdateLogo()
{
    // TODO: Update LOGO screen variables here!

    framesCounter++;    // Count frames

    // Wait for 2 seconds (120 frames) before jumping to TITLE screen
    if (framesCounter > 120)
    {
        memset(sprites, 0, sizeof(sprites));
        InitSprites(MAX_SPRITES);
        SetCurrentPhase(TitlePhase);
    }
}

void UpdateTitle()
{
    UpdateRandomRects();

    // Press enter to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        memset(sprites, 0, sizeof(sprites));
        InitSprites(MAX_SPRITES);
        InitLayers(map->ly_head, map);
        camera.offset.x = GetScreenWidth()/2;
        camera.offset.y = GetScreenHeight()/2;
        camera.target.x = camera.target.y = 0;
        camera.rotation = 0;
        camera.zoom = 1;
        SetCurrentPhase(GameplayPhase);
    }
}

void UpdateGameplay()
{
    UpdateSprites();

    // Press enter to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER))
    {
        memset(sprites, 0, sizeof(sprites));
        CloseSprites();
        SetCurrentPhase(EndingPhase);
        return;
    }

    if (IsMouseButtonDown(0)) {
        Vector2 move = GetMouseDelta();
        camera.target.x -= move.x;
        camera.target.y -= move.y;
    }
}

void UpdateEnding()
{
    // TODO: Update ENDING screen variables here!

    // Press enter to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        memset(sprites, 0, sizeof(sprites));
        InitSprites(MAX_SPRITES);
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
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    DrawSprites();
    DrawText("TITLE SCREEN", 0, 0, 40, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 0, 40, 20, DARKGREEN);
}

void DrawGameplay()
{
    // TODO: Draw GAMEPLAY screen here!
    ClearBackground(ColorFromTMX(map->backgroundcolor));
    BeginMode2D(camera);
    DrawSprites();
    EndMode2D();
    DrawText("GAMEPLAY SCREEN", 0, 0, 40, MAROON);
    DrawText("PRESS ENTER to JUMP to ENDING SCREEN", 0, 40, 20, MAROON);
}

void DrawEnding()
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawText("ENDING SCREEN", 0, 0, 40, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 0, 40, 20, DARKBLUE);
}