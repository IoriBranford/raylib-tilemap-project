#ifndef E222BE36_5310_48C7_9586_70543D02A1F0
#define E222BE36_5310_48C7_9586_70543D02A1F0

#include <tmx.h>
#include <raylib-aseprite.h>
#include <raymath.h>
#include <util.h>

typedef struct Sprite Sprite;
typedef void (*SpriteFunction)(Sprite*);

pool_typedef(Sprite, SpritePool);

typedef enum SpriteType {
    SPRITETYPE_NONE,
    SPRITETYPE_CAMERA,
    SPRITETYPE_RECTANGLE,
    SPRITETYPE_TEXTURE,
    SPRITETYPE_TEXT,
    SPRITETYPE_TILE,
    SPRITETYPE_SHAPE,
    SPRITETYPE_TILELAYER,
    SPRITETYPE_ASEPRITETAG,
    SPRITETYPE_TYPES
} SpriteType;

typedef struct SpriteBehavior {
    SpriteType type;
    SpriteFunction update, draw;
} SpriteBehavior;

typedef struct SpriteText {
    Font font;
    const char *text;
    float fontSize;
    float spacing;
    float halign;   // 0 = left, 1 = right
    float valign;   // 0 = top, 1 = bottom
    bool wrap;
} SpriteText;

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
    float z;
    union {
        struct {
            float originX, originY;
        };
        Vector2 origin;
    };
    float rotationDeg;
    union {
        struct {
            unsigned char red, green, blue, alpha;
        };
        Color color;
    };
    bool active;
    unsigned animSpeedMS;
    float animTimer;

    SpriteBehavior behavior;
    union SpriteContent {
        struct SpriteTexture {
            Texture2D *texture;
            Rectangle source;
        } texture;

        SpriteText text;

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

        AsepriteTag asepriteTag;

        float cameraZoom;
    };
};

void InitSprites(unsigned n);
void CloseSprites();

void PruneSprites();
void UpdateSprites();
int SpriteZYXSort(const void *ap, const void *bp);
void SortSprites(int (*compare)(const void*,const void*));
void DrawSprites();

size_t NumSpritesActive();
size_t NumSpritesFree();

Sprite* NewRectangleSprite(Rectangle rect, Vector2 origin, float rotationDeg, Color color);
Sprite* NewTextSprite(SpriteText *text, Rectangle rect, Color color);
Sprite* NewTMXObjectSprite(tmx_object *o, tmx_map *map, Color color);
Sprite* NewTileSprite(tmx_tile *tile, Rectangle rect, float rotationDeg, Color color);
Sprite* NewTileLayerSprite(tmx_layer *layer, tmx_map *map);
void GetTileOrigin(Vector2 *origin, tmx_tile *tile, Vector2 destSize);
void SetSpriteTile(Sprite *g, tmx_tile *tile, Vector2 flip);
tmx_tile* GetTMXObjectTile(tmx_object *o, tmx_map *map);
Sprite* NewSpriteCamera(Camera2D camera, Color color);

bool IsNearCamera2D(Vector2 position, Camera2D Camera);
bool IsSpriteNearCamera(Sprite *sprite);

void ReleaseSprite(Sprite* sprite);

#endif /* E222BE36_5310_48C7_9586_70543D02A1F0 */
