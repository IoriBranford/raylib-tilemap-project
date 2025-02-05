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

    lclass_newuserdata(l, Sprite, s);
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
    lclass_newuserdata(l, Sprite, sprite);
    return 1;
}

int L_Sprite_text(lua_State *l) {
    Rectangle rect = {
        .x = luaL_optnumber(l, 2, 0),
        .y = luaL_optnumber(l, 3, 0),
        .width = luaL_optnumber(l, 4, INFINITY),
        .height = luaL_optnumber(l, 5, INFINITY)
    };
    Color color = L_toColor(l, 6);
    SpriteText text = {
        .spacing = 1
    };
    Sprite *spr = NewTextSprite(&text, rect, color);
    if (lua_istable(l, 1)) {
        lua_getfield(l, 1, "text");
        SetSpriteText(spr, luaL_optstring(l, -1, " "));
        lua_pop(l, 1);
        lua_getfield(l, 1, "fontsize");
        spr->text.fontSize = luaL_optnumber(l, -1, spr->text.font.baseSize);
        lua_pop(l, 1);
        lua_getfield(l, 1, "spacing");
        spr->text.spacing = luaL_optnumber(l, -1, spr->text.spacing);
        lua_pop(l, 1);
        lua_getfield(l, 1, "halign");
        spr->text.halign = luaL_optnumber(l, -1, 0);
        lua_pop(l, 1);
        lua_getfield(l, 1, "valign");
        spr->text.valign = luaL_optnumber(l, -1, 0);
        lua_pop(l, 1);
        lua_getfield(l, 1, "wrap");
        spr->text.wrap = lua_toboolean(l, -1);
        lua_pop(l, 1);
        
        // TODO fontfamily
    } else {
        SetSpriteText(spr, lua_tostring(l, 1));
    }
    
    lclass_newuserdata(l, Sprite, spr);
    return 1;
}

#define sprite_getter(SPRTYPE, sprcontent, fieldtype, field) \
int L_Sprite_get##field(lua_State *l) { \
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite"); \
    if ((**o).behavior.type != SPRITETYPE_##SPRTYPE) \
        return 0; \
    lua_push##fieldtype(l, (**o).sprcontent.field); \
    return 1; \
}

#define sprite_getter_ud(SPRTYPE, sprcontent, cls, p, field) \
int L_Sprite_get##field(lua_State *l) { \
    Sprite *spr = *(Sprite**)luaL_checkudata(l, 1, "Sprite"); \
    if (spr->behavior.type != SPRITETYPE_##SPRTYPE) \
        return 0; \
    cls p*od = lua_newuserdata(l, sizeof(cls*)); \
    *od = spr->sprcontent.field; \
    luaL_setmetatable(l, #cls); \
    return 1; \
}

#define sprite_setter(SPRTYPE, sprcontent, fieldtype, field) \
int L_Sprite_set##field(lua_State *l) { \
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite"); \
    if ((**o).behavior.type != SPRITETYPE_##SPRTYPE) \
        return 0; \
    (**o).sprcontent.field = luaL_check##fieldtype(l, 2); \
    return 0; \
}

#define sprite_setterf(SPRTYPE, sprcontent, fieldtype, field, f) \
int L_Sprite_set##field(lua_State *l) { \
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite"); \
    if ((**o).behavior.type != SPRITETYPE_##SPRTYPE) \
        return 0; \
    f(*o, luaL_check##fieldtype(l, 2)); \
    return 0; \
}

#define sprite_setterf_ud(SPRTYPE, sprcontent, cls, p, field, f) \
int L_Sprite_set##field(lua_State *l) { \
    Sprite *spr = *(Sprite**)luaL_checkudata(l, 1, "Sprite"); \
    if (spr->behavior.type != SPRITETYPE_##SPRTYPE) \
        return 0; \
    cls p o = *(cls p*)luaL_checkudata(l, 2, #cls); \
    f(spr, o); \
    return 0; \
}

lclass_index_and_newindex(Sprite)
lclass_gc(Sprite, *, ReleaseSprite)
lclass_getter(Sprite, *, boolean, active)
lclass_getter_and_setter(Sprite, *, number, x)
lclass_getter_and_setter(Sprite, *, number, y)
lclass_getter_and_setter(Sprite, *, number, z)
lclass_getter_and_setter(Sprite, *, number, width)
lclass_getter_and_setter(Sprite, *, number, height)
lclass_getter_and_setter(Sprite, *, number, rotationDeg)
lclass_getter_and_setter(Sprite, *, number, originX)
lclass_getter_and_setter(Sprite, *, number, originY)
lclass_getter(Sprite, *, number, red)
lclass_getter(Sprite, *, number, green)
lclass_getter(Sprite, *, number, blue)
lclass_getter(Sprite, *, number, alpha)
lclass_setter_clamped(Sprite, *, red, 0, 255)
lclass_setter_clamped(Sprite, *, green, 0, 255)
lclass_setter_clamped(Sprite, *, blue, 0, 255)
lclass_setter_clamped(Sprite, *, alpha, 0, 255)
lclass_getter_and_setter(Sprite, *, number, animSpeedMS)
lclass_getter(Sprite, *, number, animTimer)
lclass_getter_and_setter_Vector2(Sprite, *, position)
lclass_getter_and_setter_Vector2(Sprite, *, size)
lclass_getter_and_setter_Vector2(Sprite, *, origin)
lclass_getter_and_setter_Color(Sprite, *, color)
lclass_getterf(Sprite, *, boolean, nearcamera, IsSpriteNearCamera)
lclass_setterf(Sprite, *, number, tileflipx, SetSpriteTileFlipX)
lclass_setterf(Sprite, *, number, tileflipy, SetSpriteTileFlipY)

sprite_getter(TEXT, text, string, text)
sprite_setterf(TEXT, text, string, text, SetSpriteText)
sprite_getter_ud(TILE, tile, tmx_tile, *, tile)
sprite_setterf_ud(TILE, tile, tmx_tile, *, tile, SetSpriteTile)

int L_Sprite_gettileSourceSize(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_TILE)
        return 0;
    lua_pushnumber(l, (**o).tile.source.width);
    lua_pushnumber(l, (**o).tile.source.height);
    return 2;
}

int L_Sprite_settileSourceSize(lua_State *l) {
    Sprite **o = (Sprite **)luaL_checkudata(l, 1, "Sprite");
    if ((**o).behavior.type != SPRITETYPE_TILE)
        return 0;
    (**o).tile.source.width = luaL_checknumber(l, 2);
    (**o).tile.source.height = luaL_checknumber(l, 3);
    return 0;
}

lclass_func_1_ud(Sprite, *, settilenamed,
    SetSpriteNamedTileFromCurrentTileset, string,
    tmx_tile, *, )
lclass_func_1_ud(Sprite, *, settilenamedifnew,
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

lclass_luaopen(Sprite,
    lclass_method_reg(Sprite, __index),
    lclass_method_reg(Sprite, __newindex),
    lclass_method_reg(Sprite, __gc),
    lclass_getter_reg(Sprite, active),
    lclass_getter_reg(Sprite, nearcamera),
    lclass_getter_and_setter_reg(Sprite, x),
    lclass_getter_and_setter_reg(Sprite, y),
    lclass_getter_and_setter_reg(Sprite, z),
    lclass_getter_and_setter_reg(Sprite, width),
    lclass_getter_and_setter_reg(Sprite, height),
    lclass_getter_and_setter_reg(Sprite, rotationDeg),
    lclass_getter_and_setter_reg(Sprite, originX),
    lclass_getter_and_setter_reg(Sprite, originY),
    lclass_getter_and_setter_reg(Sprite, red),
    lclass_getter_and_setter_reg(Sprite, green),
    lclass_getter_and_setter_reg(Sprite, blue),
    lclass_getter_and_setter_reg(Sprite, alpha),
    lclass_getter_and_setter_reg(Sprite, animSpeedMS),
    lclass_getter_and_setter_reg(Sprite, cameraZoom),
    lclass_getter_reg(Sprite, animTimer),
    lclass_getter_and_setter_reg(Sprite, position),
    lclass_getter_and_setter_reg(Sprite, size),
    lclass_getter_and_setter_reg(Sprite, color),
    lclass_getter_and_setter_reg(Sprite, origin),
    lclass_getter_and_setter_reg(Sprite, text),
    lclass_getter_and_setter_reg(Sprite, tile),
    lclass_getter_and_setter_reg(Sprite, tileSourceSize),
    lclass_setter_reg(Sprite, tilenamed),
    lclass_setter_reg(Sprite, tilenamedifnew),
    lclass_setter_reg(Sprite, tileflipx),
    lclass_setter_reg(Sprite, tileflipy)
)

int luaopen_gfx2d(lua_State *l) {
    luaL_Reg staticMethods[] = {
        lclass_method_reg(Sprite, rectangle),
        lclass_method_reg(Sprite, camera),
        lclass_method_reg(Sprite, text),
        {0}
    };
    luaL_register(l, "sprite", staticMethods);
    lua_pop(l, 1);

    lua_cpcall(l, luaopen_Sprite, NULL);

    return 0;
}