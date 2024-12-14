#include "game.h"

#include "engine.h"
#include "raylib.h"

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

void InitGame()
{
    SetCurrentPhase(LogoPhase);
}

void UpdateLogo()
{
    // TODO: Update LOGO screen variables here!

    framesCounter++;    // Count frames

    // Wait for 2 seconds (120 frames) before jumping to TITLE screen
    if (framesCounter > 120)
    {
        SetCurrentPhase(TitlePhase);
    }
}

void UpdateTitle()
{
    // TODO: Update TITLE screen variables here!

    // Press enter to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        SetCurrentPhase(GameplayPhase);
    }
}

void UpdateGameplay()
{
    // TODO: Update GAMEPLAY screen variables here!

    // Press enter to change to ENDING screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        SetCurrentPhase(EndingPhase);
    }
}

void UpdateEnding()
{
    // TODO: Update ENDING screen variables here!

    // Press enter to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
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
    DrawText("TITLE SCREEN", 0, 0, 40, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 0, 40, 20, DARKGREEN);
}

void DrawGameplay()
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), PURPLE);
    DrawText("GAMEPLAY SCREEN", 0, 0, 40, MAROON);
    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 0, 40, 20, MAROON);
}

void DrawEnding()
{
    // TODO: Draw ENDING screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);
    DrawText("ENDING SCREEN", 0, 0, 40, DARKBLUE);
    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 0, 40, 20, DARKBLUE);
}