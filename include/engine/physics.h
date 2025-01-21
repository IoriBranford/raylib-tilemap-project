#ifndef FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D
#define FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D

#include <engine/gfx2d.h>
#include <chipmunk.h>

void InitPhysics();
void ClosePhysics();
void UpdatePhysics();

cpBody* NewBody(cpFloat x, cpFloat y, cpFloat rotationRad);
cpBody* NewTMXObjectBody(tmx_object *obj, tmx_map *map);
cpBody* GiveBodyTMXObjectShapes(cpBody *body, tmx_object *obj, tmx_tile **maptiles, cpVect offset);
cpBody* GiveBodyTMXLayerShapes(cpBody *body, tmx_layer *layer, tmx_map *map, cpVect offset);
cpBody* GiveSpaceBodyTMXObjectShapes(tmx_object *obj, tmx_map *map);
cpBody* GiveSpaceBodyTMXLayerShapes(tmx_layer *layer, tmx_map *map);
void ReleaseBody(cpBody *body);
void ReleaseOrphanedShape(cpShape *shape);

cpCircleShape* AddBodyCircle(cpBody *body, cpFloat radius, cpFloat ox, cpFloat oy);
cpPolyShape* AddBodyRectangle(cpBody *body, cpFloat w, cpFloat h, cpFloat ox, cpFloat oy);

void UpdateSpriteFromBody(cpBody *body, Sprite *sprite);

#endif /* FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D */
