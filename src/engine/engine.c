#include "engine.h"

#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void Nop() {}

static Phase currentPhase = {
    .update = Nop,
    .draw = Nop
};

void SetCurrentPhase(Phase newPhase) {
    currentPhase = newPhase;
}

void InitEngine() {
    const int screenWidth = 480*2;
    const int screenHeight = 270*2;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    InitAudioDevice();
    // TODO: Initialize all required variables and load all required data here!
    //--------------------------------------------------------------------------------------
}

void UpdateEngine() {
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

void RunEngine() {
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateEngine, 0, 1);
#else
    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
        UpdateEngine();
#endif
}

void StopEngine() {
    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}