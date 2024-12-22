#include <box2d/box2d.h>
#include <engine.h>

static b2WorldId worldId;

void ClosePhysics();

void InitPhysics(float lengthUnitsPerMeter) {
    if (B2_IS_NON_NULL(worldId))
        ClosePhysics();
    b2SetLengthUnitsPerMeter(lengthUnitsPerMeter);
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity.y = 0;
	worldId = b2CreateWorld(&worldDef);
}

void ClosePhysics() {
    if (B2_IS_NON_NULL(worldId))
        b2DestroyWorld(worldId);
    worldId = (b2WorldId){0};
}

void UpdatePhysics() {
    b2World_Step(worldId, 1, 4);
}

b2BodyId NewBody(Vector2 position, float rotationRad) {
    b2BodyDef def = b2DefaultBodyDef();
    def.position = (b2Vec2){ position.x, position.y };
    b2CosSin rotation = b2ComputeCosSin(rotationRad);
    def.rotation = (b2Rot){ rotation.cosine, rotation.sine };
    def.fixedRotation = true;
    return b2CreateBody(worldId, &def);
}

b2ShapeId AddBodyCircle(b2BodyId body, Vector2 center, float radius, Vector2 offset) {
    b2Circle circle = {
        .center = (b2Vec2){ offset.x, offset.y },
        .radius = radius
    };
    b2ShapeDef def = b2DefaultShapeDef();
    return b2CreateCircleShape(body, &def, &circle);
}

b2ShapeId AddBodyRectangle(b2BodyId body, Vector2 halfSize, Vector2 offset, float rotationRad) {
    b2CosSin rotation = b2ComputeCosSin(rotationRad);
    b2Polygon box = b2MakeOffsetBox(halfSize.x, halfSize.y,
        (b2Vec2){offset.x, offset.y},
        (b2Rot){ rotation.cosine, rotation.sine });
    b2ShapeDef def = b2DefaultShapeDef();
    return b2CreatePolygonShape(body, &def, &box);
}

void UpdateSpriteFromBody(b2BodyId body, Sprite *sprite) {
    b2Vec2 position = b2Body_GetPosition(body);
    b2Rot rot = b2Body_GetRotation(body);
    sprite->position = (Vector2){ position.x, position.y };
    sprite->rotationDeg = RAD2DEG * b2Atan2(rot.s, rot.c);
}