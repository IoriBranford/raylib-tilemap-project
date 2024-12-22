#ifndef FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D
#define FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D

#include <engine/gfx2d.h>
#include <box2d/box2d.h>

void InitPhysics(float lengthUnitsPerMeter);
void ClosePhysics();
void UpdatePhysics();

b2BodyId NewBody(Vector2 position, float rotationRad);
b2ShapeId AddBodyCircle(b2BodyId body, Vector2 center, float radius, Vector2 offset);
b2ShapeId AddBodyRectangle(b2BodyId body, Vector2 halfSize, Vector2 offset, float rotationRad);

void UpdateSpriteFromBody(b2BodyId body, Sprite *sprite);

#endif /* FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D */
