%module gfx2d
%include <typemaps.i>
%nodefaultctor;

%{
#include <engine/gfx2d.h>
%}

%rename(NumActive) NumSpritesActive;
%rename(NumFree) NumSpritesFree;
size_t NumSpritesActive();
size_t NumSpritesFree();

Sprite* NewRectangle(float x = 0, float y = 0, float width = 1, float height = 1, float originX = 0, float originY = 0, float rotationDeg = 0, unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 255);
Sprite* FromTMXObject(tmx_object *o, tmx_tile **maptiles, unsigned char red = 255, unsigned char green = 255, unsigned char blue = 255, unsigned char alpha = 255);

struct Sprite {
    // union {
    //     struct {
            float x, y, width, height;
        // };
        // Rectangle rect;
        // struct {
        //     Vector2 position, size;
        // };
    // };
    // union {
    //     struct {
            float originX, originY;
        // };
        // Vector2 origin;
    // };
    float rotationDeg;
    // union {
    //     struct {
            unsigned char red, green, blue, alpha;
        // };
        // Color color;
    // };
    unsigned animSpeedMS;

    %immutable;
    float animTimer;
    // union SpriteContent {
    //     struct SpriteTexture {
    //         Texture2D *texture;
    //         Rectangle source;
    //     } texture;

    //     // SpriteText text;

    //     struct SpriteTile {
    //         Texture2D *texture;
    //         Rectangle source;
    //         tmx_tile *tile;
    //         unsigned frame;
    //     } tile;

    //     struct SpriteLayer {
    //         tmx_layer *layer;
    //         tmx_map *map;
    //     } layer;

    //     struct SpriteShape {
    //         tmx_shape;
    //         float thick;
    //         bool closed;
    //     } shape;

    //     // AsepriteTag asepriteTag;
    // };

    %extend {
        ~Sprite() {
            ReleaseSprite($self);
        }

        void Destroy() {
            ReleaseSprite($self);
        }

        void GetColor(unsigned char *OUTPUT, unsigned char *OUTPUT, unsigned char *OUTPUT, unsigned char *OUTPUT);

        void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
            $self->color = (Color){r, g, b, a};
        }

        // bool IsOnScreen() {
        //     return IsSpriteOnScreen($self);
        // }
    }
};

%{
Sprite* NewRectangle(float x, float y, float width, float height, float originX, float originY, float rotationDeg, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    return NewRectangleSprite(
        (Rectangle){x, y, width, height},
        (Vector2){originX, originY},
        rotationDeg,
        (Color){red, green, blue, alpha}
    );
}
Sprite* FromTMXObject(tmx_object *o, tmx_tile **maptiles, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
    return NewTMXObjectSprite(0, maptiles, (Color){red, green, blue, alpha});
}

void Sprite_GetColor(Sprite *self, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *a){
    *r = self->red;
    *g = self->green;
    *b = self->blue;
    *a = self->alpha;
};
%}