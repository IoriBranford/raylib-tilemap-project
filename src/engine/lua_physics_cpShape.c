#include "lua_physics.h"

int L_cpShape_NewCircleShape(lua_State *l) {
    cpBody **body = luaL_testudata(l, 1, "cpBody");
    cpFloat radius = luaL_optnumber(l, 2, 1);
    cpVect offset = cpv(luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0));
    cpShape *shape = cpCircleShapeNew(body ? *body : NULL, radius, offset);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);
    return 1;
}

int L_cpShape_NewSegmentShape(lua_State *l) {
    cpBody **body = luaL_testudata(l, 1, "cpBody");
    cpVect a = cpv(luaL_checknumber(l, 2), luaL_checknumber(l, 3));
    cpVect b = cpv(luaL_checknumber(l, 4), luaL_checknumber(l, 5));
    cpFloat radius = luaL_optnumber(l, 6, 0);
    cpShape *shape = cpSegmentShapeNew(body ? *body : NULL, a, b, radius);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);
    return 1;
}

int L_cpShape_NewPolyShape(lua_State *l) {
    cpBody **body = luaL_testudata(l, 1, "cpBody");

    int argType = lua_type(l, 2);

    int nVertArgs = 0;
    if (argType == LUA_TTABLE) {
        nVertArgs = lua_objlen(l, 2);
    } else if (argType == LUA_TNUMBER) {
        nVertArgs = lua_gettop(l) - 1;
    }

    if (nVertArgs % 2 != 0)
        luaL_error(l, "expected even number of point components { x1, y1, x2, y2, ... }");
    else if (nVertArgs == 0)
        luaL_error(l, "expected point components { x1, y1, x2, y2, ... }");
    
    int nVerts = nVertArgs / 2;
    cpVect *verts = calloc(sizeof(cpVect), nVerts);
    cpVect *vert = verts;
    if (argType == LUA_TTABLE) {
        for (int i = 2; i <= nVertArgs; i += 2) {
            lua_rawgeti(l, 2, i-1);
            lua_rawgeti(l, 2, i);
            vert->x = luaL_checknumber(l, -2);
            vert->y = luaL_checknumber(l, -1);
            lua_pop(l, 2);
            ++vert;
        }
    } else if (argType == LUA_TNUMBER) {
        int nArgs = nVertArgs + 1;
        for (int i = 2; i <= nVertArgs; i += 2) {
            vert->x = luaL_checknumber(l, i);
            vert->y = luaL_checknumber(l, i+1);
            ++vert;
        }
    }

    cpShape *shape = cpPolyShapeNew(body ? *body : NULL, nVerts, verts, cpTransformIdentity, 0);
    cpShapeSetUserData(shape, (cpDataPointer)LUA_REFNIL);
    class_newuserdata(l, cpShape, shape);

    free(verts);
    return 1;
}

class_index_and_newindex(cpShape)
class_gc(cpShape, *, ReleaseOrphanedShape)
class_getterf_and_setterf_ud(cpShape, *, cpBody, *, Body, cpShapeGetBody, cpShapeSetBody)
class_getterf_and_setterf(cpShape, *, number, Mass, cpShapeGetMass, cpShapeSetMass)
class_getterf_and_setterf(cpShape, *, number, Density, cpShapeGetDensity, cpShapeSetDensity)
class_getterf(cpShape, *, number, Moment, cpShapeGetMoment)
class_getterf(cpShape, *, number, Area, cpShapeGetArea)
class_getterf_vec2(cpShape, *, cpVect, CenterOfGravity, cpShapeGetCenterOfGravity)
class_getterf_and_setterf(cpShape, *, boolean, Sensor, cpShapeGetSensor, cpShapeSetSensor)
class_getterf_and_setterf(cpShape, *, number, Elasticity, cpShapeGetElasticity, cpShapeSetElasticity)
class_getterf_and_setterf(cpShape, *, number, Friction, cpShapeGetFriction, cpShapeSetFriction)
class_getterf_and_setterf_vec2(cpShape, *, cpVect, SurfaceVelocity, cpShapeGetSurfaceVelocity, cpShapeSetSurfaceVelocity)
cp_getter_and_setter_userdata(cpShape)

int L_cpShape_getFilter(lua_State *l) {
    cpShape **shape = luaL_checkudata(l, 1, "cpShape");
    cpShapeFilter filter = cpShapeGetFilter(*shape);
    lua_pushinteger(l, filter.group);
    lua_pushinteger(l, filter.categories);
    lua_pushinteger(l, filter.mask);
    return 3;
}

int L_cpShape_setFilter(lua_State *l) {
    cpShape **shape = luaL_checkudata(l, 1, "cpShape");
    cpShapeFilter filter = cpShapeGetFilter(*shape);
    if (lua_isnumber(l, 2)) filter.group = floor(lua_tonumber(l, 2));
    if (lua_isnumber(l, 3)) filter.categories = floor(lua_tonumber(l, 3));
    if (lua_isnumber(l, 4)) filter.mask = floor(lua_tonumber(l, 4));
    cpShapeSetFilter(*shape, filter);
    return 0;
}

int L_cpShape_RemoveFromSpace(lua_State *l) {
    cpShape **ud = luaL_checkudata(l, 1, "cpShape");
    cpSpace *space = cpShapeGetSpace(*ud);
    if (space)
        cpSpaceRemoveShape(space, *ud);
    return 0;
}

class_luaopen(cpShape,
    class_method_reg(cpShape, NewCircleShape),
    class_method_reg(cpShape, NewSegmentShape),
    class_method_reg(cpShape, NewPolyShape),
    class_method_reg(cpShape, __index),
    class_method_reg(cpShape, __newindex),
    class_method_reg(cpShape, __gc),
    class_getter_and_setter_reg(cpShape, Body),
    class_getter_and_setter_reg(cpShape, Mass),
    class_getter_and_setter_reg(cpShape, Density),
    class_getter_reg(cpShape, Moment),
    class_getter_reg(cpShape, Area),
    class_getter_reg(cpShape, CenterOfGravity),
    class_getter_and_setter_reg(cpShape, Sensor),
    class_getter_and_setter_reg(cpShape, Elasticity),
    class_getter_and_setter_reg(cpShape, Friction),
    class_getter_and_setter_reg(cpShape, SurfaceVelocity),
    class_getter_and_setter_reg(cpShape, Filter),
    class_getter_and_setter_reg(cpShape, UserData),
    class_method_reg(cpShape, RemoveFromSpace)
)