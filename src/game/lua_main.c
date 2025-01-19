#include <engine.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

int main() {
    const int screenWidth = 480*2;
    const int screenHeight = 270*2;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");
    InitAudioDevice();

    ResetLuaEngine("main", 0);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateLuaEngine, 0, 1);
#else
    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    // Main game loop
    while (IsLuaEngineRunning()) {
        if (WindowShouldClose())    // Detect window close button or ESC key
            StopLuaEngine();
        else
            UpdateLuaEngine();
    }
#endif
    // De-Initialization
    //--------------------------------------------------------------------------------------

    CloseAudioDevice();

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}