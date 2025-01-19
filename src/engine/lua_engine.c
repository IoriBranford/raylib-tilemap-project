#include "engine.h"
#include "raylib.h"

static bool running = true;
static bool resetting = false;
static char *mainScript = NULL;
static int mainScriptPriority = 0;

void ResetLuaEngine(const char *nextMainScript, int priority) {
    resetting = true;
    if (nextMainScript) {
        mainScript = MemRealloc(mainScript, TextLength(nextMainScript)+1);
        TextCopy(mainScript, nextMainScript);
    } else {
        if (mainScript)
            MemFree(mainScript);
        mainScript = NULL;
    }
}

void UpdateLuaEngine() {
    if (resetting) {
        resetting = false;

        CloseLua();
        ClosePhysics();
        CloseSprites();
        CloseTasks();

        if (mainScript) {
            InitPhysics();
            InitSprites(2048);
            InitTasks(2048);
            InitLua();
            RunLua(mainScript, mainScriptPriority, NULL);
            MemFree(mainScript);
            mainScript = NULL;
        } else {
            running = false;
            return;
        }
    }
    // Update
    //----------------------------------------------------------------------------------
    UpdatePhysics();
    UpdateSprites();

    RunTasks();

    PruneTasks();
    SortTasks();

    PruneSprites();
    SortSprites(SpriteZYXSort);

    UpdateLua();
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(BLACK);
    DrawSprites();
    EndDrawing();
    //----------------------------------------------------------------------------------
}

bool IsLuaEngineRunning() {
    return running;
}

void StopLuaEngine() {
    running = false;
}