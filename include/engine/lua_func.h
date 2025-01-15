#ifndef AF748BAB_8CD4_4319_906B_B206A59C10F9
#define AF748BAB_8CD4_4319_906B_B206A59C10F9

#define l_func_0_0(f) int L_##f(lua_State *l) { f(); return 0; }
#define l_func_1_0(f, at) int L_##f(lua_State *l) { f(lua_check##at(l, 1)); return 0; }
#define l_func_0_1(f, rt) int L_##f(lua_State *l) { lua_push##rt(l, f()); return 1; }
#define l_func_1_1(f, at, rt) int L_##f(lua_State *l) { lua_push##rt(l, f(lua_check##at(l, 1))); return 1; }

#define l_func_reg(f) {.name = #f, .func = L_##f}

#endif /* AF748BAB_8CD4_4319_906B_B206A59C10F9 */
