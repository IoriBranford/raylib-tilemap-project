#ifndef DE86D8AF_A774_40B0_A498_829E1AA1A3DA
#define DE86D8AF_A774_40B0_A498_829E1AA1A3DA

#include <func.h>

typedef struct Phase {
    Function update, draw;
} Phase;

void SetCurrentPhase(Phase newPhase);
void InitEngine();
void RunEngine();
void StopEngine();

#endif /* DE86D8AF_A774_40B0_A498_829E1AA1A3DA */
