#ifndef A3BF049D_B4C7_433F_B3EA_80433D9B6312
#define A3BF049D_B4C7_433F_B3EA_80433D9B6312

typedef struct _tmx_map tmx_map;

tmx_map* LoadMap(const char *path);
void UnloadMap(tmx_map* map);

#endif /* A3BF049D_B4C7_433F_B3EA_80433D9B6312 */
