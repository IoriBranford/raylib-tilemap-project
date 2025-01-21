#include <engine/lua.h>
#include "gfx2d.h"

int L_Sprite_rectangle(lua_State *l) {
    if (!NumSpritesFree())
        return 0;

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
        L_toColor(l, 8)
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
    Color color = L_toColor(l, 7);
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

class_func_1_ud(Sprite, *, settilenamed,
    SetSpriteNamedTileFromCurrentTileset, string,
    tmx_tile, *, )
class_func_1_ud(Sprite, *, settilenamedifnew,
    SetSpriteNamedTileFromCurrentTilesetIfNew, string,
    tmx_tile, *, )

int L_Sprite_getcameraZoom(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_CAMERA)
        return 0;
    lua_pushnumber(l, (**o).cameraZoom);
    return 1;
}

int L_Sprite_setcameraZoom(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_CAMERA)
        return 0;
    (**o).cameraZoom = luaL_checknumber(l, 2);
    return 0;
}

class_luaopen(Sprite,
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
    class_getter_and_setter_reg(Sprite, position),
    class_getter_and_setter_reg(Sprite, size),
    class_getter_and_setter_reg(Sprite, color),
    class_getter_and_setter_reg(Sprite, origin),
    class_setter_reg(Sprite, tilenamed),
    class_setter_reg(Sprite, tilenamedifnew),
    class_setter_reg(Sprite, tileflipx),
    class_setter_reg(Sprite, tileflipy)
)

int luaopen_gfx2d(lua_State *l) {
    luaL_Reg staticMethods[] = {
        class_method_reg(Sprite, rectangle),
        class_method_reg(Sprite, camera),
        class_method_reg(Sprite, cameraend),
        {0}
    };
    luaL_register(l, "sprite", staticMethods);
    lua_pop(l, 1);

    lua_cpcall(l, luaopen_Sprite, NULL);

    return 0;
}