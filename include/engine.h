#ifndef DE86D8AF_A774_40B0_A498_829E1AA1A3DA
#define DE86D8AF_A774_40B0_A498_829E1AA1A3DA

#include <engine/gfx2d.h>

typedef struct Phase {
    void (*update)();
    void (*draw)();
} Phase;

void SetCurrentPhase(Phase newPhase);
void InitEngine();
void RunEngine();
void StopEngine();

#endif /* DE86D8AF_A774_40B0_A498_829E1AA1A3DA */
