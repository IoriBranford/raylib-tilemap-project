#include <engine/lua.h>
#include <raylib.h>

// Input-related functions: keyboard
lfunc_1_1(IsKeyPressed, integer, boolean)
lfunc_1_1(IsKeyPressedRepeat, integer, boolean)
lfunc_1_1(IsKeyDown, integer, boolean)
lfunc_1_1(IsKeyReleased, integer, boolean)
lfunc_1_1(IsKeyUp, integer, boolean)
lfunc_0_1(GetKeyPressed, integer)
lfunc_0_1(GetCharPressed, integer)
lfunc_1_0(SetExitKey, integer)

// Input-related functions: gamepads
lfunc_1_1(IsGamepadAvailable, integer, boolean)
lfunc_1_1(GetGamepadName, integer, string)
lfunc_2_1(IsGamepadButtonPressed, integer, integer, boolean)
lfunc_2_1(IsGamepadButtonDown, integer, integer, boolean)
lfunc_2_1(IsGamepadButtonReleased, integer, integer, boolean)
lfunc_2_1(IsGamepadButtonUp, integer, integer, boolean)
lfunc_0_1(GetGamepadButtonPressed, integer)
lfunc_1_1(GetGamepadAxisCount, integer, integer)
lfunc_2_1(GetGamepadAxisMovement, integer, integer, number)
lfunc_1_1(SetGamepadMappings, string, integer)
lfunc_4_0(SetGamepadVibration, integer, number, number, number)

// Input-related functions: mouse
lfunc_1_1(IsMouseButtonPressed, integer, boolean)
lfunc_1_1(IsMouseButtonDown, integer, boolean)
lfunc_1_1(IsMouseButtonReleased, integer, boolean)
lfunc_1_1(IsMouseButtonUp, integer, boolean)
lfunc_0_1(GetMouseX, integer)
lfunc_0_1(GetMouseY, integer)
lfunc_0_vec2(GetMousePosition, Vector2)
lfunc_0_vec2(GetMouseDelta, Vector2)
lfunc_2_0(SetMousePosition, integer, integer)
lfunc_2_0(SetMouseOffset, integer, integer)
lfunc_2_0(SetMouseScale, number, number)
lfunc_0_1(GetMouseWheelMove, number)
lfunc_0_vec2(GetMouseWheelMoveV, Vector2)
lfunc_1_0(SetMouseCursor, integer)

    // Input-related functions: touch TODO if needed
    // lfunc_0_1(GetTouchX, integer)                                    // Get touch position X for touch point 0 (relative to screen size)
    // lfunc_0_1(GetTouchY, integer)                                    // Get touch position Y for touch point 0 (relative to screen size)
    // lfunc_1_vec2(GetTouchPosition, integer, Vector2)                    // Get touch position XY for a touch point index (relative to screen size)
    // lfunc_1_1(GetTouchPointId, integer, integer)                         // Get touch point identifier for given index
    // lfunc_0_1(GetTouchPointCount, integer)                           // Get number of touch points

    //------------------------------------------------------------------------------------
    // Gestures and Touch Handling Functions (Module: rgestures)
    //------------------------------------------------------------------------------------
    // RLAPI void SetGesturesEnabled(unsigned int flags);      // Enable a set of gestures using flags
    // RLAPI bool IsGestureDetected(unsigned int gesture);     // Check if a gesture have been detected
    // RLAPI int GetGestureDetected(void);                     // Get latest detected gesture
    // RLAPI float GetGestureHoldDuration(void);               // Get gesture hold time in seconds
    // RLAPI Vector2 GetGestureDragVector(void);               // Get gesture drag vector
    // RLAPI float GetGestureDragAngle(void);                  // Get gesture drag angle
    // RLAPI Vector2 GetGesturePinchVector(void);              // Get gesture pinch delta
    // RLAPI float GetGesturePinchAngle(void);                 // Get gesture pinch angle

int luaopen_rlinput(lua_State *l)
{
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

    lua_getglobal(l, ("_G"));
    luaL_Reg r[] = {{.name = "IsKeyPressed", .func = L_IsKeyPressed}, {.name = "IsKeyPressedRepeat", .func = L_IsKeyPressedRepeat}, {.name = "IsKeyDown", .func = L_IsKeyDown}, {.name = "IsKeyReleased", .func = L_IsKeyReleased}, {.name = "IsKeyUp", .func = L_IsKeyUp}, {.name = "GetKeyPressed", .func = L_GetKeyPressed}, {.name = "GetCharPressed", .func = L_GetCharPressed}, {.name = "SetExitKey", .func = L_SetExitKey}, {.name = "IsGamepadAvailable", .func = L_IsGamepadAvailable}, {.name = "GetGamepadName", .func = L_GetGamepadName}, {.name = "IsGamepadButtonPressed", .func = L_IsGamepadButtonPressed}, {.name = "IsGamepadButtonPressed", .func = L_IsGamepadButtonPressed}, {.name = "IsGamepadButtonDown", .func = L_IsGamepadButtonDown}, {.name = "IsGamepadButtonReleased", .func = L_IsGamepadButtonReleased}, {.name = "IsGamepadButtonUp", .func = L_IsGamepadButtonUp}, {.name = "GetGamepadButtonPressed", .func = L_GetGamepadButtonPressed}, {.name = "GetGamepadAxisCount", .func = L_GetGamepadAxisCount}, {.name = "GetGamepadAxisMovement", .func = L_GetGamepadAxisMovement}, {.name = "SetGamepadMappings", .func = L_SetGamepadMappings}, {.name = "SetGamepadVibration", .func = L_SetGamepadVibration}, {.name = "IsMouseButtonPressed", .func = L_IsMouseButtonPressed}, {.name = "IsMouseButtonDown", .func = L_IsMouseButtonDown}, {.name = "IsMouseButtonReleased", .func = L_IsMouseButtonReleased}, {.name = "IsMouseButtonUp", .func = L_IsMouseButtonUp}, {.name = "GetMouseX", .func = L_GetMouseX}, {.name = "GetMouseY", .func = L_GetMouseY}, {.name = "GetMousePosition", .func = L_GetMousePosition}, {.name = "GetMouseDelta", .func = L_GetMouseDelta}, {.name = "SetMousePosition", .func = L_SetMousePosition}, {.name = "SetMouseOffset", .func = L_SetMouseOffset}, {.name = "SetMouseScale", .func = L_SetMouseScale}, {.name = "GetMouseWheelMove", .func = L_GetMouseWheelMove}, {.name = "GetMouseWheelMoveV", .func = L_GetMouseWheelMoveV}, {.name = "SetMouseCursor", .func = L_SetMouseCursor}, {0}};
    luaL_register(l, NULL, r);
    L_docfuncs_reg(l, r);
    return 0;
}