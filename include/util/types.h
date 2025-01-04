#ifndef E636567A_1B4D_4313_95E2_7D36D6E3E464
#define E636567A_1B4D_4313_95E2_7D36D6E3E464

#include <raylib.h>
#include <tmx.h>

static inline Vector2 VECTOR2(float x, float y) {
    return (Vector2){x, y};
}

static inline Color tmx2rl_Color(uint32_t color) {
	tmx_col_bytes res = tmx_col_to_bytes(color);
	return *((Color*)&res);
}

#endif /* E636567A_1B4D_4313_95E2_7D36D6E3E464 */
