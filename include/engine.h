#ifndef DE86D8AF_A774_40B0_A498_829E1AA1A3DA
#define DE86D8AF_A774_40B0_A498_829E1AA1A3DA

#include <engine/assets.h>
#include <engine/gfx2d.h>
#include <engine/lua.h>
#include <engine/tasks.h>
#include <engine/physics.h>

typedef struct Phase {
    void (*update)();
    void (*draw)();
} Phase;

void SetCurrentPhase(Phase newPhase);
void InitEngine();
void RunEngine();
void StopEngine();

void ResetLuaEngine(const char *nextMainScript, int priority);
void UpdateLuaEngine();
bool IsLuaEngineRunning();
void StopLuaEngine();

#endif /* DE86D8AF_A774_40B0_A498_829E1AA1A3DA */
