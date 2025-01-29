#include <engine/physics.h>

static cpSpace *space;

void InitPhysics() {
    if (space)
        ClosePhysics();
    space = cpSpaceNew();
}

void FreeSpaceShape(cpSpace *sp, cpShape *shape, void *_) {
    cpSpaceRemoveShape(sp, shape);
    cpShapeFree(shape);
}

void FreeSpaceConstraint(cpSpace *sp, cpConstraint *constraint, void *_) {
    cpSpaceRemoveConstraint(sp, constraint);
    cpConstraintFree(constraint);
}

void FreeSpaceBody(cpSpace *sp, cpBody *body, void *_) {
    cpSpaceRemoveBody(sp, body);
    cpBodyFree(body);
}

void ReleaseEachSpaceBody(cpBody *body, void *_) {
    ReleaseBody(body);
}

void ReleaseEachSpaceShape(cpSpace *sp, cpShape *shape, void *_) {
    if (cpSpaceIsLocked(sp))
        cpSpaceAddPostStepCallback(sp, (cpPostStepFunc)FreeSpaceShape, shape, NULL);
    else
        FreeSpaceShape(sp, shape, NULL);
}

void ReleaseEachSpaceConstraint(cpSpace *sp, cpConstraint *constraint, void *_) {
    if (cpSpaceIsLocked(sp))
        cpSpaceAddPostStepCallback(sp, (cpPostStepFunc)FreeSpaceConstraint, constraint, NULL);
    else
        FreeSpaceConstraint(sp, constraint, NULL);
}

void ReleaseSpace(cpSpace *sp) {
    if (space) {
        cpSpaceEachBody(space, (cpSpaceBodyIteratorFunc)ReleaseEachSpaceBody, NULL);
        cpSpaceEachShape(space, (cpSpaceShapeIteratorFunc)ReleaseEachSpaceShape, NULL);
        cpSpaceEachConstraint(space, (cpSpaceConstraintIteratorFunc)ReleaseEachSpaceConstraint, NULL);
        cpSpaceFree(space);
    }
}

void ClosePhysics() {
    ReleaseSpace(space);
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
    if (sp) {
        if (cpSpaceIsLocked(sp))
            cpSpaceAddPostStepCallback(sp, (cpPostStepFunc)FreeSpaceShape, shape, NULL);
        else
            FreeSpaceShape(sp, shape, NULL);
    } else {
        cpShapeFree(shape);
    }
}

void ReleaseEachBodyConstraint(cpBody *body, cpConstraint *constraint, void *_) {
    cpSpace *sp = cpConstraintGetSpace(constraint);
    if (sp) {
        if (cpSpaceIsLocked(sp))
            cpSpaceAddPostStepCallback(sp, (cpPostStepFunc)FreeSpaceConstraint, constraint, NULL);
        else
            FreeSpaceConstraint(sp, constraint, NULL);
    } else {
        cpConstraintFree(constraint);
    }
}

void ReleaseBody(cpBody *body) {
    cpBodyEachConstraint(body, (cpBodyConstraintIteratorFunc)ReleaseEachBodyConstraint, NULL);
    cpBodyEachShape(body, (cpBodyShapeIteratorFunc)ReleaseEachBodyShape, NULL);
    cpSpace *sp = cpBodyGetSpace(body);
    if (sp) {
        if (cpSpaceIsLocked(sp))
            cpSpaceAddPostStepCallback(sp, (cpPostStepFunc)FreeSpaceBody, body, NULL);
        else
            FreeSpaceBody(sp, body, NULL);
    } else {
        cpBodyFree(body);
    }
}

void ReleaseOrphanedBody(cpBody *body) {
    if (!cpBodyGetSpace(body))
        ReleaseBody(body);
}

void ReleaseOrphanedShape(cpShape *shape) {
    if (!cpShapeGetBody(shape) && !cpShapeGetSpace(shape))
        cpShapeFree(shape);
}

cpBody* NewTMXObjectBody(tmx_object *obj, tmx_map *map) {
    cpBody *body = cpBodyNew(1, HUGE_VAL);
    cpBodySetPosition(body, cpv(obj->x, obj->y));
    cpBodySetAngle(body, obj->rotation * DEG2RAD);
    GiveBodyTMXObjectShapes(body, obj, map->tiles, cpv(0, 0));
    return body;
}

cpBody* AddNewTMXObjectBody(tmx_object *obj, tmx_map *map) {
    cpBody *body = cpBodyNew(1, HUGE_VAL);
    cpBodySetPosition(body, cpv(obj->x, obj->y));
    cpBodySetAngle(body, obj->rotation * DEG2RAD);
    cpSpaceAddBody(space, body);
    GiveBodyTMXObjectShapes(body, obj, map->tiles, cpv(0, 0));
    return body;
}

cpBody* GiveSpaceBodyTMXObjectShapes(tmx_object *obj, tmx_map *map) {
    cpBody *body = cpSpaceGetStaticBody(space);
    GiveBodyTMXObjectShapes(body, obj, map->tiles, cpv(obj->x, obj->y));
    return body;
}

cpBody* GiveSpaceBodyTMXLayerShapes(tmx_layer *layer, tmx_map *map) {
    cpBody *body = cpSpaceGetStaticBody(space);
    GiveBodyTMXLayerShapes(body, layer, map, cpv(layer->offsetx, layer->offsety));
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