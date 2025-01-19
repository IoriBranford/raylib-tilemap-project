#include <engine/lua.h>
#include <util/lua_class.h>
#include "gfx2d.h"

int L_Sprite_rectangle(lua_State *l) {
    if (!NumSpritesFree())
        return 0;

    lua_Number r = luaL_optnumber(l, 8, 255);
    lua_Number g = luaL_optnumber(l, 9, 255);
    lua_Number b = luaL_optnumber(l, 10, 255);
    lua_Number a = luaL_optnumber(l, 11, 255);

    Color color = {
        .r = r < 0 ? 0 : r > 255 ? 255 : r,
        .g = g < 0 ? 0 : g > 255 ? 255 : g,
        .b = b < 0 ? 0 : b > 255 ? 255 : b,
        .a = a < 0 ? 0 : a > 255 ? 255 : a
    };

    Sprite *s = NewRectangleSprite(
        (Rectangle){
            .x = luaL_optnumber(l, 1, 0),
            .y = luaL_optnumber(l, 2, 0),
            .width = luaL_optnumber(l, 3, 1),
            .height = luaL_optnumber(l, 4, 1)
        },

        (Vector2) {
            .x = luaL_optnumber(l, 5, 0),
            .y = luaL_optnumber(l, 6, 0)
        },

        luaL_optnumber(l, 7, 0),

        color
    );

    class_newuserdata(l, Sprite, s);
    return 1;
}

int L_Sprite_camera(lua_State *l) {
    Camera2D camera = {
        .target = {luaL_optnumber(l, 1, 0), luaL_optnumber(l, 2, 0)},
        .offset = {luaL_optnumber(l, 3, 0), luaL_optnumber(l, 4, 0)},
        .rotation = luaL_optnumber(l, 5, 0),
        .zoom = luaL_optnumber(l, 6, 1)
    };
    Color color = GetColor(luaL_optnumber(l, 7, UINT32_MAX));
    Sprite *sprite = NewSpriteCamera(camera, color);
    sprite->z = -10000000;
    class_newuserdata(l, Sprite, sprite);
    return 1;
}

int L_Sprite_cameraend(lua_State *l) {
    Camera2D camera = {.zoom = 0};
    Sprite *cameraSprite = NewSpriteCamera(camera, WHITE);
    cameraSprite->z = 10000000;
    class_newuserdata(l, Sprite, cameraSprite);
    return 1;
}

class_index_and_newindex(Sprite)
class_gc(Sprite, *, ReleaseSprite)
class_getter(Sprite, *, boolean, active)
class_getter_and_setter(Sprite, *, number, x)
class_getter_and_setter(Sprite, *, number, y)
class_getter_and_setter(Sprite, *, number, z)
class_getter_and_setter(Sprite, *, number, width)
class_getter_and_setter(Sprite, *, number, height)
class_getter_and_setter(Sprite, *, number, rotationDeg)
class_getter_and_setter(Sprite, *, number, originX)
class_getter_and_setter(Sprite, *, number, originY)
class_getter(Sprite, *, number, red)
class_getter(Sprite, *, number, green)
class_getter(Sprite, *, number, blue)
class_getter(Sprite, *, number, alpha)
class_setter_clamped(Sprite, *, red, 0, 255)
class_setter_clamped(Sprite, *, green, 0, 255)
class_setter_clamped(Sprite, *, blue, 0, 255)
class_setter_clamped(Sprite, *, alpha, 0, 255)
class_getter_and_setter(Sprite, *, number, animSpeedMS)
class_getter(Sprite, *, number, animTimer)
class_getter_and_setter_Vector2(Sprite, *, position)
class_getter_and_setter_Vector2(Sprite, *, size)
class_getter_and_setter_Vector2(Sprite, *, origin)
class_getter_and_setter_Color(Sprite, *, color)
class_getterf(Sprite, *, boolean, nearcamera, IsSpriteNearCamera)
class_setterf(Sprite, *, number, tileflipx, SetSpriteTileFlipX)
class_setterf(Sprite, *, number, tileflipy, SetSpriteTileFlipY)

class_func_1_ud(Sprite, *, __settilenamed,
    SetSpriteNamedTileFromCurrentTileset, string,
    tmx_tile, *, )
class_func_1_ud(Sprite, *, __settilenamedifnew,
    SetSpriteNamedTileFromCurrentTilesetIfNew, string,
    tmx_tile, *, )

int L_Sprite___getcameraZoom(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_CAMERA)
        return 0;
    lua_pushnumber(l, (**o).cameraZoom);
    return 1;
}

int L_Sprite___setcameraZoom(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_CAMERA)
        return 0;
    (**o).cameraZoom = luaL_checknumber(l, 2);
    return 0;
}

int luaopen_gfx2d(lua_State *l) {
    luaL_Reg staticMethods[] = {
        class_method_reg(Sprite, rectangle),
        class_method_reg(Sprite, camera),
        class_method_reg(Sprite, cameraend),
        {0}
    };
    luaL_register(l, "sprite", staticMethods);
    lua_pop(l, 1);

    luaL_newmetatable(l, "Sprite");
    luaL_Reg instanceMethods[] = {
        class_method_reg(Sprite, __index),
        class_method_reg(Sprite, __newindex),
        class_method_reg(Sprite, __gc),
        class_getter_reg(Sprite, active),
        class_getter_reg(Sprite, nearcamera),
        class_getter_and_setter_reg(Sprite, x),
        class_getter_and_setter_reg(Sprite, y),
        class_getter_and_setter_reg(Sprite, z),
        class_getter_and_setter_reg(Sprite, width),
        class_getter_and_setter_reg(Sprite, height),
        class_getter_and_setter_reg(Sprite, rotationDeg),
        class_getter_and_setter_reg(Sprite, originX),
        class_getter_and_setter_reg(Sprite, originY),
        class_getter_and_setter_reg(Sprite, red),
        class_getter_and_setter_reg(Sprite, green),
        class_getter_and_setter_reg(Sprite, blue),
        class_getter_and_setter_reg(Sprite, alpha),
        class_getter_and_setter_reg(Sprite, animSpeedMS),
        class_getter_and_setter_reg(Sprite, cameraZoom),
        class_getter_reg(Sprite, animTimer),
        class_getter_and_setter_multi_reg(Sprite, position),
        class_getter_and_setter_multi_reg(Sprite, size),
        class_getter_and_setter_multi_reg(Sprite, color),
        class_getter_and_setter_multi_reg(Sprite, origin),
        class_setter_reg(Sprite, tilenamed),
        class_setter_reg(Sprite, tilenamedifnew),
        class_setter_reg(Sprite, tileflipx),
        class_setter_reg(Sprite, tileflipy),
        {0}
    };
    luaL_register(l, NULL, instanceMethods);
    lua_pop(l, 1);

    return 0;
}