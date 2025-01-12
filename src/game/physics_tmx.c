#include <game/physics.h>
#include <tmx.h>
#include <stdio.h>

const cpFloat SHAPE_BEVEL = 1;

static const cpVect ALIGNMENT_ORIGIN[OA_BOTTOMRIGHT+1] = {
    [OA_NONE]       = {0.0, 1.0},
    [OA_TOPLEFT]    = {0.0, 0.0},
    [OA_TOP]        = {0.5, 0.0},
    [OA_TOPRIGHT]   = {1.0, 0.0},
    [OA_LEFT]       = {0.0, 0.5},
    [OA_CENTER]     = {0.5, 0.5},
    [OA_RIGHT]      = {1.0, 0.5},
    [OA_BOTTOMLEFT] = {0.0, 1.0},
    [OA_BOTTOM]     = {0.5, 1.0},
    [OA_BOTTOMRIGHT]= {1.0, 1.0},
};

cpBody* GiveBodyTMXShape(cpBody *body, tmx_object *obj, tmx_tile **maptiles, cpVect offset) {
    tmx_property *collidable = tmx_get_property(obj->properties, "collidable");
    if (!collidable || !collidable->value.boolean)
        return body;

    switch (obj->obj_type) {
        case OT_POINT: {
            cpCircleShapeNew(body, .5f, offset);
        } break;
        case OT_ELLIPSE: {
            double radius = (obj->width + obj->height)/4;
            cpCircleShapeNew(body, radius, cpv(offset.x + radius, offset.y + radius));
        } break;
        case OT_SQUARE: {
            cpBoxShapeNew2(body, (cpBB) {
                .l = offset.x,
                .t = offset.y,
                .r = offset.x + obj->width,
                .b = offset.y + obj->height
            }, SHAPE_BEVEL);
        } break;
        case OT_POLYGON: {
            tmx_shape *shape = obj->content.shape;
            cpVect *verts = calloc(shape->points_len, sizeof(cpVect));
            for (int i = 0; i < shape->points_len; ++i) {
                verts[i].x = offset.x + shape->points[i][0];
                verts[i].y = offset.y + shape->points[i][1];
            }
            cpPolyShapeNew(body, shape->points_len, verts, cpTransformIdentity, SHAPE_BEVEL);
            free(verts);
        } break;
        case OT_POLYLINE: {
            tmx_shape *shape = obj->content.shape;
            cpVect a = {
                offset.x + shape->points[0][0],
                offset.y + shape->points[0][1]
            };
            for (int i = 1; i < shape->points_len; ++i) {
                cpVect b = {
                    offset.x + shape->points[i][0],
                    offset.y + shape->points[i][1]
                };
                cpSegmentShapeNew(body, a, b, SHAPE_BEVEL);
                a = b;
            }
        } break;
        case OT_TILE: {
            tmx_tile *tile = maptiles[obj->content.gid];
            if (!tile) {
                fprintf(stderr, "no tile with gid %d", obj->content.gid);
                break;
            }

            offset = ALIGNMENT_ORIGIN[tile->tileset->objectalignment];
            offset.x *= -tile->width;
            offset.y *= -tile->height;
            offset.x += tile->tileset->x_offset;
            offset.y += tile->tileset->y_offset;

            for (tmx_object *col = tile->collision; col; col = col->next)
                GiveBodyTMXShape(body, col, maptiles, offset);
        } break;
    }

    return body;
}

cpBody* NewBodyFromTMXObject(tmx_object *obj, tmx_tile **maptiles) {
    cpBody *body = cpBodyNewKinematic();
    GiveBodyTMXShape(body, obj, maptiles, cpv(0, 0));
    cpBodySetPosition(body, cpv(obj->x, obj->y));
    cpBodySetAngle(body, obj->rotation * DEG2RAD);
    return body;
}