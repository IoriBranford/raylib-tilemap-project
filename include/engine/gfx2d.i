%module gfx2d
%{
#include <engine/gfx2d.h>
%}

%nodefaultctor;
%nodefaultdtor;
%delobject ReleaseSprite;

struct Sprite {
    union {
        struct {
            float x, y, width, height;
        };
        Rectangle rect;
        struct {
            Vector2 position, size;
        };
    };
    Vector2 origin;
    float rotationDeg;
    Color color;
    unsigned animSpeedMS;

    %immutable;
    float animTimer;
    union SpriteContent {
        struct SpriteTexture {
            Texture2D *texture;
            Rectangle source;
        } texture;

        // SpriteText text;

        struct SpriteTile {
            Texture2D *texture;
            Rectangle source;
            tmx_tile *tile;
            unsigned frame;
        } tile;

        struct SpriteLayer {
            tmx_layer *layer;
            tmx_map *map;
        } layer;

        struct SpriteShape {
            tmx_shape;
            float thick;
            bool closed;
        } shape;

        // AsepriteTag asepriteTag;
    };
};

size_t NumSpritesActive();
size_t NumSpritesFree();

void ReleaseSprite(Sprite* sprite);

%newobject RectangleSprite;
%newobject TMXObjectSprite;

%inline %{
Sprite* RectangleSprite(float x, float y, float width, float height) {
    return NewRectangleSprite(
        (Rectangle){x, y, width, height},
        (Vector2){0},
        0.0f,
        WHITE
    );
}
Sprite* TMXObjectSprite(tmx_object *o, tmx_tile **maptiles) {
    return NewTMXObjectSprite(0, maptiles, WHITE);    
}
%}

%extend Sprite {
    ~Sprite() {
        ReleaseSprite($self);
    }
}