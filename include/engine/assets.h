#ifndef A3BF049D_B4C7_433F_B3EA_80433D9B6312
#define A3BF049D_B4C7_433F_B3EA_80433D9B6312

typedef struct _tmx_text tmx_text;
void* LoadTMXFont(const char *dir, tmx_text *text);
void UnloadTMXFont(void *ptr);

#endif /* A3BF049D_B4C7_433F_B3EA_80433D9B6312 */
