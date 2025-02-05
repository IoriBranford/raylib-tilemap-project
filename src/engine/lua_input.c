#include <engine/lua.h>
#include <engine/input.h>

lfunc_2_0(MapInputToAction, string, string)

int L_MapInputsToActions(lua_State *l) {
    int n = 0;
    if (lua_istable(l, 1)) {
        lua_pushnil(l);
        while (lua_next(l, 1)) {
            if (lua_isstring(l, -2) && lua_isstring(l, -1)) {
                MapInputToAction(lua_tostring(l, -2), lua_tostring(l, -1));
                ++n;
            }
            lua_pop(l, 1);
        }
    }
    lua_pushinteger(l, n);
    return 1;
}

lfunc_1_1(IsActionPressed, string, boolean)
lfunc_1_1(IsActionDown, string, boolean)
lfunc_1_1(IsActionReleased, string, boolean)
lfunc_1_1(GetActionPosition, string, number)

l_global_funcs_luaopen(input, 
    lfunc_reg(MapInputToAction),
    lfunc_reg(MapInputsToActions),
    lfunc_reg(IsActionPressed),
    lfunc_reg(IsActionDown),
    lfunc_reg(IsActionReleased),
    lfunc_reg(GetActionPosition)
)