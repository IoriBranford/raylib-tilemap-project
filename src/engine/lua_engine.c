#include "engine.h"
#include "raylib.h"

static bool running = true;
static bool resetting = false;
static char *mainScript = NULL;
static int mainScriptPriority = 0;
static int mainScriptRef = LUA_REFNIL;

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
    UnrefLuaTask(mainScriptRef);
    mainScriptRef = LUA_REFNIL;
}

bool IsMainTaskDone() {
    Task *mainScriptTask = GetLuaTask(mainScriptRef);
    return !mainScriptTask || IsTaskDone(mainScriptTask);
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
            mainScriptRef = RunLua(mainScript, mainScriptPriority, NULL);
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
    if (IsMainTaskDone()) {
        if (!resetting)
            StopLuaEngine();
        return;
    }
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
    ResetLuaEngine(NULL, 0);
}