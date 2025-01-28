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
reg_class_method(Sprite, getcameraZoom)

int L_Sprite_setcameraZoom(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_CAMERA)
        return 0;
    (**o).cameraZoom = luaL_checknumber(l, 2);
    return 0;
}
reg_class_method(Sprite, setcameraZoom)

class_luaopen(Sprite,
    reg_Sprite___index,
    reg_Sprite___newindex,
    reg_Sprite___gc,
    reg_Sprite_getactive,
    reg_Sprite_getnearcamera,
    reg_Sprite_getx,
    reg_Sprite_gety,
    reg_Sprite_getz,
    reg_Sprite_getwidth,
    reg_Sprite_getheight,
    reg_Sprite_getrotationDeg,
    reg_Sprite_getoriginX,
    reg_Sprite_getoriginY,
    reg_Sprite_getred,
    reg_Sprite_getgreen,
    reg_Sprite_getblue,
    reg_Sprite_getalpha,
    reg_Sprite_getanimSpeedMS,
    reg_Sprite_getcameraZoom,
    reg_Sprite_setx,
    reg_Sprite_sety,
    reg_Sprite_setz,
    reg_Sprite_setwidth,
    reg_Sprite_setheight,
    reg_Sprite_setrotationDeg,
    reg_Sprite_setoriginX,
    reg_Sprite_setoriginY,
    reg_Sprite_setred,
    reg_Sprite_setgreen,
    reg_Sprite_setblue,
    reg_Sprite_setalpha,
    reg_Sprite_setanimSpeedMS,
    reg_Sprite_setcameraZoom,
    reg_Sprite_getanimTimer,
    reg_Sprite_getposition,
    reg_Sprite_getsize,
    reg_Sprite_getcolor,
    reg_Sprite_getorigin,
    reg_Sprite_setposition,
    reg_Sprite_setsize,
    reg_Sprite_setcolor,
    reg_Sprite_setorigin,
    reg_Sprite_settilenamed,
    reg_Sprite_settilenamedifnew,
    reg_Sprite_settileflipx,
    reg_Sprite_settileflipy
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

    doc_class(Sprite, "2d graphic object",
        doc_class_ctors(Sprite)
        doc_class_fields(Sprite,
            doc_var(x, number, "read/write - x position", NULL),
            doc_var(y, number, "read/write - y position", NULL),
            doc_var(z, number, "read/write - z position", NULL),
            doc_var(width, number,  "read/write - rectangle width", NULL),
            doc_var(height, number, "read/write - rectangle height", NULL),
            doc_var(rotationDeg, number, "read/write - rotation in degrees", NULL),
            doc_var(originX, number, "read-write - x position of the pivot point on rectangle", NULL),
            doc_var(originY, number, "read-write - y position of the pivot point on rectangle", NULL),
            doc_var(color, integer, "read/write - color in the form 0xRRGGBBAA", NULL),
            doc_var(animSpeedMS, number, "read/write - number of milliseconds to animate sprite per-frame", NULL),
            doc_var(animTimer, number, "read-only - number of milliseconds in the current animation state", NULL),
            doc_var(nearcamera, boolean, "read-only - is close enough to the center of the camera", NULL),
            doc_var(tileflipx, number, "write-only - -1 to flip, +1 to unflip", NULL),
            doc_var(tileflipy, number, "write-only - -1 to flip, +1 to unflip", NULL),
            doc_var(tilenamed, string, "write only - set to the name of a tile stringid defined in tileset properties", NULL),
            doc_var(tilenamedifnew, string, "write only - as tilenamed, but preserve current animation state if already this tile", NULL)
        )
        doc_class_methods(Sprite))

    doc_module(gfx2d, "Graphics 2d",
        doc_module_constants()
        doc_module_classes(Sprite)
        doc_module_funcs())

    return 0;
}