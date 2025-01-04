#include <game/physics.h>

static cpSpace *space;

void InitPhysics() {
    if (space)
        ClosePhysics();
    space = cpSpaceNew();
}

void ClosePhysics() {
    if (space)
        cpSpaceDestroy(space);
    space = NULL;
}

void UpdatePhysics() {
    cpSpaceStep(space, 1);
}

cpBody* NewBody(cpFloat x, cpFloat y, cpFloat rotationRad) {
    cpBody *body = cpBodyNew(1, INFINITY);
    cpBodySetPosition(body, cpv(x, y));
    cpBodySetAngle(body, rotationRad);
    cpSpaceAddBody(space, body);
    return body;
}

cpCircleShape* AddBodyCircle(cpBody *body, cpFloat radius, cpFloat ox, cpFloat oy) {
    cpCircleShape *circle = cpCircleShapeNew(body, radius, cpv(ox, oy));
    cpSpaceAddShape(space, circle);
    return circle;
}

cpPolyShape* AddBodyRectangle(cpBody *body, cpFloat w, cpFloat h, cpFloat ox, cpFloat oy) {
    cpVect verts[] = {
        cpv(0, 0),
        cpv(0, h),
        cpv(w, h),
        cpv(w, 0)
    };
    cpPolyShape *poly = cpPolyShapeNew(body, 4, verts, cpTransformIdentity, 0);
    cpSpaceAddShape(space, poly);
    return poly;
}

void UpdateSpriteFromBody(cpBody *body, Sprite *sprite) {
    cpVect position = cpBodyGetPosition(body);
    cpFloat angle = cpBodyGetAngle(body);
    sprite->position = (Vector2){ position.x, position.y };
    sprite->rotationDeg = RAD2DEG * angle;
}