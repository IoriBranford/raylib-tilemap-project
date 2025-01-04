#ifndef F368B866_5240_4102_BE90_898768165E85
#define F368B866_5240_4102_BE90_898768165E85

#ifdef __cplusplus
extern "C" {
#endif

void InitLua();
void CloseLua();

int RunLua(const char *luaFile);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* F368B866_5240_4102_BE90_898768165E85 */
