#include <engine/lua.h>
#include <util/lua_class.h>
#include <chipmunk.h>

int L_physics_newbody(lua_State *l) {
    cpFloat mass = luaL_optnumber(l, 1, 0);
    cpFloat moment = luaL_optnumber(l, 2, INFINITY);
    class_newuserdata(l, cpBody, cpBodyNew(mass, moment));
    return 1;
}

class_index_and_newindex(cpBody)
class_gc(cpBody, cpBodyDestroy)

int luaopen_physics(lua_State *l) {
    luaL_Reg staticMethods[] = {
        class_method_reg(physics, newbody),
        {0}
    };
    luaL_register(l, "physics", staticMethods);
    lua_pop(l, 1);

    luaL_newmetatable(l, "cpBody");
    luaL_Reg bodyMethods[] = {
        class_method_reg(cpBody, __index),
        class_method_reg(cpBody, __newindex),
        class_method_reg(cpBody, __gc),
        {0}
    };
    luaL_register(l, NULL, bodyMethods);
    lua_pop(l, 1);

    return 0;
}