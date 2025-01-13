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
    cpBody *body = cpBodyNew(1, HUGE_VAL);
    cpBodySetPosition(body, cpv(x, y));
    cpBodySetAngle(body, rotationRad);
    cpSpaceAddBody(space, body);
    return body;
}

void ReleaseEachBodyShape(cpBody *body, cpShape *shape, void *_) {
    cpSpace *sp = cpShapeGetSpace(shape);
    if (sp)
        cpSpaceRemoveShape(sp, shape);
    cpShapeFree(shape);
}

void ReleaseEachBodyConstraint(cpBody *body, cpConstraint *constraint, void *_) {
    cpSpace *sp = cpConstraintGetSpace(constraint);
    if (sp)
        cpSpaceRemoveConstraint(sp, constraint);
    cpConstraintFree(constraint);
}

void ReleaseBody(cpBody *body) {
    cpBodyEachShape(body, ReleaseEachBodyShape, NULL);
    cpBodyEachConstraint(body, ReleaseEachBodyConstraint, NULL);
    cpSpace *sp = cpBodyGetSpace(body);
    if (sp)
        cpSpaceRemoveBody(sp, body);
    cpBodyFree(body);
}

cpBody* GiveBodyTMXShape(cpBody *body, tmx_object *obj, tmx_tile **maptiles, cpVect offset);

cpBody* NewTMXObjectBody(tmx_object *obj, tmx_tile **maptiles) {
    cpBody *body = cpBodyNew(1, HUGE_VAL);
    cpBodySetPosition(body, cpv(obj->x, obj->y));
    cpBodySetAngle(body, obj->rotation * DEG2RAD);
    cpSpaceAddBody(space, body);
    GiveBodyTMXShape(body, obj, maptiles, cpv(0, 0));
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