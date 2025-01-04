#ifndef FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D
#define FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D

#include <engine/gfx2d.h>
#include <chipmunk.h>

void InitPhysics();
void ClosePhysics();
void UpdatePhysics();

cpBody* NewBody(cpFloat x, cpFloat y, cpFloat rotationRad);
cpShape* AddBodyCircle(cpBody *body, cpFloat radius, cpFloat ox, cpFloat oy);
cpShape* AddBodyRectangle(cpBody *body, cpFloat w, cpFloat h, cpFloat ox, cpFloat oy);

void UpdateSpriteFromBody(cpBody *body, Sprite *sprite);

#endif /* FCFFDAB1_9263_4EE0_8FDC_99B9DAFFB84D */
