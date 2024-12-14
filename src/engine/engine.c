#include "engine.h"

#include "raylib.h"


static void Nop() {}

static Phase currentPhase = {
    .update = Nop,
    .draw = Nop
};

void SetCurrentPhase(Phase newPhase) {
    currentPhase = newPhase;
}

void InitEngine() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    // TODO: Initialize all required variables and load all required data here!

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    //--------------------------------------------------------------------------------------
}

void RunEngine() {
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        currentPhase.update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        currentPhase.draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
}

void StopEngine() {
    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}