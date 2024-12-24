#ifndef E636567A_1B4D_4313_95E2_7D36D6E3E464
#define E636567A_1B4D_4313_95E2_7D36D6E3E464

#include <raylib.h>
#include <box2d/box2d.h>

static inline Vector2 VECTOR2(float x, float y) {
    return (Vector2){x, y};
}

static inline b2Vec2 b2VEC2(float x, float y) {
    return (b2Vec2){x, y};
}

static inline b2Vec2 Vec2rl2b2(Vector2 v) {
    return (b2Vec2){v.x, v.y};
}

static inline Vector2 Vec2b2torl(b2Vec2 v) {
    return (Vector2){v.x, v.y};
}

#endif /* E636567A_1B4D_4313_95E2_7D36D6E3E464 */
