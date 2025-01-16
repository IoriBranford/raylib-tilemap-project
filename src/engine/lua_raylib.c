#include <engine/lua.h>
#include <util/lua_class.h>
#include <raylib.h>

// Cursor-related functions
l_func_0_0(ShowCursor)
l_func_0_0(HideCursor)
l_func_0_0(IsCursorHidden)
l_func_0_0(EnableCursor)
l_func_0_0(DisableCursor)
l_func_0_0(IsCursorOnScreen)

// Timing-related functions
l_func_1_0(SetTargetFPS, integer)
l_func_0_1(GetFrameTime, number)
l_func_0_1(GetTime, number)
l_func_0_1(GetFPS, integer)

// Misc. functions
l_func_1_0(TakeScreenshot, string)
l_func_1_0(OpenURL, string)

// Input-related functions: keyboard
l_func_1_1(IsKeyPressed, integer, boolean)
l_func_1_1(IsKeyPressedRepeat, integer, boolean)
l_func_1_1(IsKeyDown, integer, boolean)
l_func_1_1(IsKeyReleased, integer, boolean)
l_func_1_1(IsKeyUp, integer, boolean)
l_func_0_1(GetKeyPressed, integer)
l_func_0_1(GetCharPressed, integer)
l_func_1_0(SetExitKey, integer)

// Input-related functions: gamepads
l_func_1_1(IsGamepadAvailable, integer, boolean)
l_func_1_1(GetGamepadName, integer, string)
l_func_2_1(IsGamepadButtonPressed, integer, integer, boolean)
l_func_2_1(IsGamepadButtonDown, integer, integer, boolean)
l_func_2_1(IsGamepadButtonReleased, integer, integer, boolean)
l_func_2_1(IsGamepadButtonUp, integer, integer, boolean)
l_func_0_1(GetGamepadButtonPressed, integer)
l_func_1_1(GetGamepadAxisCount, integer, integer)
l_func_2_1(GetGamepadAxisMovement, integer, integer, number)
l_func_1_1(SetGamepadMappings, string, integer)
l_func_4_0(SetGamepadVibration, integer, number, number, number)

// Input-related functions: mouse
l_func_1_1(IsMouseButtonPressed, integer, boolean)
l_func_1_1(IsMouseButtonDown, integer, boolean)
l_func_1_1(IsMouseButtonReleased, integer, boolean)
l_func_1_1(IsMouseButtonUp, integer, boolean)
l_func_0_1(GetMouseX, integer)
l_func_0_1(GetMouseY, integer)
l_func_0_vec2(GetMousePosition, Vector2)
l_func_0_vec2(GetMouseDelta, Vector2)
l_func_2_0(SetMousePosition, integer, integer)
l_func_2_0(SetMouseOffset, integer, integer)
l_func_2_0(SetMouseScale, number, number)
l_func_0_1(GetMouseWheelMove, number)
l_func_0_vec2(GetMouseWheelMoveV, Vector2)
l_func_1_0(SetMouseCursor, integer)

// Color/pixel related functions
l_func_3_Color(ColorFromHSV, number, number, number)

int luaopen_raylib(lua_State *l) {
    l_global_enum(l, KEY_NULL            );
    l_global_enum(l, KEY_APOSTROPHE      );
    l_global_enum(l, KEY_COMMA           );
    l_global_enum(l, KEY_MINUS           );
    l_global_enum(l, KEY_PERIOD          );
    l_global_enum(l, KEY_SLASH           );
    l_global_enum(l, KEY_ZERO            );
    l_global_enum(l, KEY_ONE             );
    l_global_enum(l, KEY_TWO             );
    l_global_enum(l, KEY_THREE           );
    l_global_enum(l, KEY_FOUR            );
    l_global_enum(l, KEY_FIVE            );
    l_global_enum(l, KEY_SIX             );
    l_global_enum(l, KEY_SEVEN           );
    l_global_enum(l, KEY_EIGHT           );
    l_global_enum(l, KEY_NINE            );
    l_global_enum(l, KEY_SEMICOLON       );
    l_global_enum(l, KEY_EQUAL           );
    l_global_enum(l, KEY_A               );
    l_global_enum(l, KEY_B               );
    l_global_enum(l, KEY_C               );
    l_global_enum(l, KEY_D               );
    l_global_enum(l, KEY_E               );
    l_global_enum(l, KEY_F               );
    l_global_enum(l, KEY_G               );
    l_global_enum(l, KEY_H               );
    l_global_enum(l, KEY_I               );
    l_global_enum(l, KEY_J               );
    l_global_enum(l, KEY_K               );
    l_global_enum(l, KEY_L               );
    l_global_enum(l, KEY_M               );
    l_global_enum(l, KEY_N               );
    l_global_enum(l, KEY_O               );
    l_global_enum(l, KEY_P               );
    l_global_enum(l, KEY_Q               );
    l_global_enum(l, KEY_R               );
    l_global_enum(l, KEY_S               );
    l_global_enum(l, KEY_T               );
    l_global_enum(l, KEY_U               );
    l_global_enum(l, KEY_V               );
    l_global_enum(l, KEY_W               );
    l_global_enum(l, KEY_X               );
    l_global_enum(l, KEY_Y               );
    l_global_enum(l, KEY_Z               );
    l_global_enum(l, KEY_LEFT_BRACKET    );
    l_global_enum(l, KEY_BACKSLASH       );
    l_global_enum(l, KEY_RIGHT_BRACKET   );
    l_global_enum(l, KEY_GRAVE           );
    l_global_enum(l, KEY_SPACE           );
    l_global_enum(l, KEY_ESCAPE          );
    l_global_enum(l, KEY_ENTER           );
    l_global_enum(l, KEY_TAB             );
    l_global_enum(l, KEY_BACKSPACE       );
    l_global_enum(l, KEY_INSERT          );
    l_global_enum(l, KEY_DELETE          );
    l_global_enum(l, KEY_RIGHT           );
    l_global_enum(l, KEY_LEFT            );
    l_global_enum(l, KEY_DOWN            );
    l_global_enum(l, KEY_UP              );
    l_global_enum(l, KEY_PAGE_UP         );
    l_global_enum(l, KEY_PAGE_DOWN       );
    l_global_enum(l, KEY_HOME            );
    l_global_enum(l, KEY_END             );
    l_global_enum(l, KEY_CAPS_LOCK       );
    l_global_enum(l, KEY_SCROLL_LOCK     );
    l_global_enum(l, KEY_NUM_LOCK        );
    l_global_enum(l, KEY_PRINT_SCREEN    );
    l_global_enum(l, KEY_PAUSE           );
    l_global_enum(l, KEY_F1              );
    l_global_enum(l, KEY_F2              );
    l_global_enum(l, KEY_F3              );
    l_global_enum(l, KEY_F4              );
    l_global_enum(l, KEY_F5              );
    l_global_enum(l, KEY_F6              );
    l_global_enum(l, KEY_F7              );
    l_global_enum(l, KEY_F8              );
    l_global_enum(l, KEY_F9              );
    l_global_enum(l, KEY_F10             );
    l_global_enum(l, KEY_F11             );
    l_global_enum(l, KEY_F12             );
    l_global_enum(l, KEY_LEFT_SHIFT      );
    l_global_enum(l, KEY_LEFT_CONTROL    );
    l_global_enum(l, KEY_LEFT_ALT        );
    l_global_enum(l, KEY_LEFT_SUPER      );
    l_global_enum(l, KEY_RIGHT_SHIFT     );
    l_global_enum(l, KEY_RIGHT_CONTROL   );
    l_global_enum(l, KEY_RIGHT_ALT       );
    l_global_enum(l, KEY_RIGHT_SUPER     );
    l_global_enum(l, KEY_KB_MENU         );
    l_global_enum(l, KEY_KP_0            );
    l_global_enum(l, KEY_KP_1            );
    l_global_enum(l, KEY_KP_2            );
    l_global_enum(l, KEY_KP_3            );
    l_global_enum(l, KEY_KP_4            );
    l_global_enum(l, KEY_KP_5            );
    l_global_enum(l, KEY_KP_6            );
    l_global_enum(l, KEY_KP_7            );
    l_global_enum(l, KEY_KP_8            );
    l_global_enum(l, KEY_KP_9            );
    l_global_enum(l, KEY_KP_DECIMAL      );
    l_global_enum(l, KEY_KP_DIVIDE       );
    l_global_enum(l, KEY_KP_MULTIPLY     );
    l_global_enum(l, KEY_KP_SUBTRACT     );
    l_global_enum(l, KEY_KP_ADD          );
    l_global_enum(l, KEY_KP_ENTER        );
    l_global_enum(l, KEY_KP_EQUAL        );
    l_global_enum(l, KEY_BACK            );
    l_global_enum(l, KEY_MENU            );
    l_global_enum(l, KEY_VOLUME_UP       );
    l_global_enum(l, KEY_VOLUME_DOWN     );

    l_global_enum(l, MOUSE_BUTTON_LEFT   );
    l_global_enum(l, MOUSE_BUTTON_RIGHT  );
    l_global_enum(l, MOUSE_BUTTON_MIDDLE );
    l_global_enum(l, MOUSE_BUTTON_SIDE   );
    l_global_enum(l, MOUSE_BUTTON_EXTRA  );
    l_global_enum(l, MOUSE_BUTTON_FORWARD);
    l_global_enum(l, MOUSE_BUTTON_BACK   );

    l_global_enum(l, MOUSE_CURSOR_DEFAULT      );
    l_global_enum(l, MOUSE_CURSOR_ARROW        );
    l_global_enum(l, MOUSE_CURSOR_IBEAM        );
    l_global_enum(l, MOUSE_CURSOR_CROSSHAIR    );
    l_global_enum(l, MOUSE_CURSOR_POINTING_HAND);
    l_global_enum(l, MOUSE_CURSOR_RESIZE_EW    );
    l_global_enum(l, MOUSE_CURSOR_RESIZE_NS    );
    l_global_enum(l, MOUSE_CURSOR_RESIZE_NWSE  );
    l_global_enum(l, MOUSE_CURSOR_RESIZE_NESW  );
    l_global_enum(l, MOUSE_CURSOR_RESIZE_ALL   );
    l_global_enum(l, MOUSE_CURSOR_NOT_ALLOWED  );

    l_global_enum(l, GAMEPAD_BUTTON_UNKNOWN);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_FACE_UP);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    l_global_enum(l, GAMEPAD_BUTTON_MIDDLE_LEFT);
    l_global_enum(l, GAMEPAD_BUTTON_MIDDLE);
    l_global_enum(l, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    l_global_enum(l, GAMEPAD_BUTTON_LEFT_THUMB);
    l_global_enum(l, GAMEPAD_BUTTON_RIGHT_THUMB);

    l_global_enum(l, GAMEPAD_AXIS_LEFT_X       );
    l_global_enum(l, GAMEPAD_AXIS_LEFT_Y       );
    l_global_enum(l, GAMEPAD_AXIS_RIGHT_X      );
    l_global_enum(l, GAMEPAD_AXIS_RIGHT_Y      );
    l_global_enum(l, GAMEPAD_AXIS_LEFT_TRIGGER );
    l_global_enum(l, GAMEPAD_AXIS_RIGHT_TRIGGER);

    l_global_enum(l, GESTURE_NONE       );
    l_global_enum(l, GESTURE_TAP        );
    l_global_enum(l, GESTURE_DOUBLETAP  );
    l_global_enum(l, GESTURE_HOLD       );
    l_global_enum(l, GESTURE_DRAG       );
    l_global_enum(l, GESTURE_SWIPE_RIGHT);
    l_global_enum(l, GESTURE_SWIPE_LEFT );
    l_global_enum(l, GESTURE_SWIPE_UP   );
    l_global_enum(l, GESTURE_SWIPE_DOWN );
    l_global_enum(l, GESTURE_PINCH_IN   );
    l_global_enum(l, GESTURE_PINCH_OUT  );

    lua_getglobal(l, "_G");
    luaL_Reg raylibFunctions[] = {
        // Cursor-related functions
        l_func_reg(ShowCursor),
        l_func_reg(HideCursor),
        l_func_reg(IsCursorHidden),
        l_func_reg(EnableCursor),
        l_func_reg(DisableCursor),
        l_func_reg(IsCursorOnScreen),

        // Timing-related functions
        l_func_reg(SetTargetFPS),
        l_func_reg(GetFrameTime),
        l_func_reg(GetTime),
        l_func_reg(GetFPS),

        // Misc. functions
        l_func_reg(TakeScreenshot),
        l_func_reg(OpenURL),

        // Input-related functions: keyboard
        l_func_reg(IsKeyPressed),
        l_func_reg(IsKeyPressedRepeat),
        l_func_reg(IsKeyDown),
        l_func_reg(IsKeyReleased),
        l_func_reg(IsKeyUp),
        l_func_reg(GetKeyPressed),
        l_func_reg(GetCharPressed),
        l_func_reg(SetExitKey),

        // Input-related functions: gamepads
        l_func_reg(IsGamepadAvailable),
        l_func_reg(GetGamepadName),
        l_func_reg(IsGamepadButtonPressed),
        l_func_reg(IsGamepadButtonPressed),
        l_func_reg(IsGamepadButtonDown),
        l_func_reg(IsGamepadButtonReleased),
        l_func_reg(IsGamepadButtonUp),
        l_func_reg(GetGamepadButtonPressed),
        l_func_reg(GetGamepadAxisCount),
        l_func_reg(GetGamepadAxisMovement),
        l_func_reg(SetGamepadMappings),
        l_func_reg(SetGamepadVibration),

        // Input-related functions: mouse
        l_func_reg(IsMouseButtonPressed),
        l_func_reg(IsMouseButtonDown),
        l_func_reg(IsMouseButtonReleased),
        l_func_reg(IsMouseButtonUp),
        l_func_reg(GetMouseX),
        l_func_reg(GetMouseY),
        l_func_reg(GetMousePosition),
        l_func_reg(GetMouseDelta),
        l_func_reg(SetMousePosition),
        l_func_reg(SetMouseOffset),
        l_func_reg(SetMouseScale),
        l_func_reg(GetMouseWheelMove),
        l_func_reg(GetMouseWheelMoveV),
        l_func_reg(SetMouseCursor),

        // Color/pixel related functions
        l_func_reg(ColorFromHSV),

        {0}
    };
    luaL_register(l, NULL, raylibFunctions);
    lua_pop(l, 1);
    return 0;
}