#include <engine/lua.h>
#include <raylib.h>
#include <math.h>

uint32_t L_toColorInt(lua_State *l, int i) {
    lua_Integer color = luaL_optinteger(l, i, UINT32_MAX);
    if (color < 0) return 0;
    if (color > UINT32_MAX) return UINT32_MAX;
    return (uint32_t)color;
}

Color L_toColor(lua_State *l, int i) {
    return GetColor(L_toColorInt(l, i));
}

// Window-related functions TODO if needed
// l_func_3_0(InitWindow, integer, integer, string) //(int width, int height, const char *title);  // Initialize window and OpenGL context
// l_func_0_0(CloseWindow)                                     // Close window and unload OpenGL context
// l_func_0_0(WindowShouldClose)                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
// l_func_0_0(IsWindowReady)                                   // Check if window has been initialized successfully
// l_func_0_0(IsWindowFullscreen)                              // Check if window is currently fullscreen
// l_func_0_0(IsWindowHidden)                                  // Check if window is currently hidden
// l_func_0_0(IsWindowMinimized)                               // Check if window is currently minimized
// l_func_0_0(IsWindowMaximized)                               // Check if window is currently maximized
// l_func_0_0(IsWindowFocused)                                 // Check if window is currently focused
// l_func_0_0(IsWindowResized)                                 // Check if window has been resized last frame
// l_func_1_0(IsWindowState, integer)                      // Check if one specific window flag is enabled
// l_func_1_0(SetWindowState, integer)                    // Set window configuration state using flags
// l_func_1_0(ClearWindowState, integer)                  // Clear window configuration state flags
// l_func_0_0(ToggleFullscreen)                                // Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
// l_func_0_0(ToggleBorderlessWindowed)                        // Toggle window state: borderless windowed, resizes window to match monitor resolution
// l_func_0_0(MaximizeWindow)                                  // Set window state: maximized, if resizable
// l_func_0_0(MinimizeWindow)                                  // Set window state: minimized, if resizable
// l_func_0_0(RestoreWindow)                                   // Set window state: not minimized/maximized
// // TODO after Image class
// // l_func_ud_0(SetWindowIcon, Image)                            // Set icon for window (single image, RGBA 32bit)
// // l_func_ud1_0(SetWindowIcons, Image, integer)              // Set icon for window (multiple images, RGBA 32bit)
// l_func_1_0(SetWindowTitle, string)                     // Set title for window
// l_func_2_0(SetWindowPosition, integer, integer)                       // Set window position on screen
// l_func_1_0(SetWindowMonitor, integer)                         // Set monitor for the current window
// l_func_2_0(SetWindowMinSize, integer, integer)               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
// l_func_2_0(SetWindowMaxSize, integer, integer)               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
// l_func_2_0(SetWindowSize, integer, integer)                  // Set window dimensions
// l_func_1_0(SetWindowOpacity, number)                       // Set window opacity [0.0f..1.0f]
// l_func_0_0(SetWindowFocused)                                // Set window focused
// // RLAPI void *GetWindowHandle(void);                                // Get native window handle
// l_func_0_1(GetScreenWidth, integer)                                   // Get current screen width
// l_func_0_1(GetScreenHeight, integer)                                  // Get current screen height
// l_func_0_1(GetRenderWidth, integer)                                   // Get current render width (it considers HiDPI)
// l_func_0_1(GetRenderHeight, integer)                                  // Get current render height (it considers HiDPI)
// l_func_0_1(GetMonitorCount, integer)                                  // Get number of connected monitors
// l_func_0_1(GetCurrentMonitor, integer)                                // Get current monitor where window is placed
// l_func_1_vec2(GetMonitorPosition, integer, Vector2);                    // Get specified monitor position
// l_func_1_1(GetMonitorWidth, integer, integer)                           // Get specified monitor width (current video mode used by monitor)
// l_func_1_1(GetMonitorHeight, integer, integer)                          // Get specified monitor height (current video mode used by monitor)
// l_func_1_1(GetMonitorPhysicalWidth, integer, integer)                   // Get specified monitor physical width in millimetres
// l_func_1_1(GetMonitorPhysicalHeight, integer, integer)                  // Get specified monitor physical height in millimetres
// l_func_1_1(GetMonitorRefreshRate, integer, integer)                     // Get specified monitor refresh rate
// l_func_0_vec2(GetWindowPosition, Vector2)                            // Get window position XY on monitor
// l_func_0_vec2(GetWindowScaleDPI, Vector2)                            // Get window scale DPI factor
// l_func_1_1(GetMonitorName, integer, string)                    // Get the human-readable, UTF-8 encoded name of the specified monitor
// l_func_1_0(SetClipboardText, string)                    // Set clipboard text content
// l_func_0_1(GetClipboardText, string)                         // Get clipboard text content
// // RLAPI Image GetClipboardImage(void);                              // Get clipboard image content
// // RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
// // RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling

// Cursor-related functions
l_func_0_0(ShowCursor)
l_func_0_0(HideCursor)
l_func_0_0(IsCursorHidden)
l_func_0_0(EnableCursor)
l_func_0_0(DisableCursor)
l_func_0_0(IsCursorOnScreen)

// Drawing-related functions TODO?

// VR stereo config functions for VR simulator TODO?

// Shader management functions TODO?

// Screen-space-related functions
// TODO after Ray, Camera, Matrix classes
// RLAPI Ray GetScreenToWorldRay(Vector2 position, Camera camera);                             // Get a ray trace from screen position (i.e mouse)
// RLAPI Ray GetScreenToWorldRayEx(Vector2 position, Camera camera, int width, int height);    // Get a ray trace from screen position (i.e mouse) in a viewport
// RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);                            // Get the screen space position for a 3d world space position
// RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height);   // Get size position for a 3d world space position
// RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);                        // Get the screen space position for a 2d camera world space position
// RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);                        // Get the world space position for a 2d camera screen space position
// RLAPI Matrix GetCameraMatrix(Camera camera);                                                // Get camera transform matrix (view matrix)
// RLAPI Matrix GetCameraMatrix2D(Camera2D camera);                                            // Get camera 2d transform matrix

// Timing-related functions
l_func_1_0(SetTargetFPS, integer)
l_func_0_1(GetFrameTime, number)
l_func_0_1(GetTime, number)
l_func_0_1(GetFPS, integer)

// Custom frame control functions probably will stay on C side

// Random values generation functions
l_func_1_0(SetRandomSeed, integer)                      // Set the seed for the random number generator
l_func_2_1(GetRandomValue, integer, integer, integer)                       // Get a random value between min and max (both included)

int L_GetRandomSequence(lua_State *l) {                // Load random values sequence, no values repeated
    lua_Integer count = luaL_checkinteger(l, 1);
    if (count <= 0) return 0;
    int *seq = LoadRandomSequence(count, luaL_checkinteger(l, 2), luaL_checkinteger(l, 3));
    lua_newtable(l);
    int *n = seq;
    for (int i = 1; i <= count; ++i, ++n) {
        lua_pushinteger(l, *n);
        lua_rawseti(l, -2, i);
    }
    UnloadRandomSequence(seq);
    return 1;
}

// RLAPI void UnloadRandomSequence(int *sequence); unnecessary

// Misc. functions
l_func_1_0(TakeScreenshot, string)
// RLAPI void SetConfigFlags(unsigned int flags); necessary?
l_func_1_0(OpenURL, string)

l_func_2_0(TraceLog, integer, string)         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
l_func_1_0(SetTraceLogLevel, integer)                        // Set the current threshold (minimum) log level

// Files management functions
// File system functions
// Compression/Encoding functionality
// TODO as needed

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

// Input-related functions: touch TODO if needed
// l_func_0_1(GetTouchX, integer)                                    // Get touch position X for touch point 0 (relative to screen size)
// l_func_0_1(GetTouchY, integer)                                    // Get touch position Y for touch point 0 (relative to screen size)
// l_func_1_vec2(GetTouchPosition, integer, Vector2)                    // Get touch position XY for a touch point index (relative to screen size)
// l_func_1_1(GetTouchPointId, integer, integer)                         // Get touch point identifier for given index
// l_func_0_1(GetTouchPointCount, integer)                           // Get number of touch points

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

// Color/pixel related functions
l_func_3_Color(ColorFromHSV, number, number, number)

int L_ColorToRGBA(lua_State *l)
{
    Color c = L_toColor(l, 1);
    lua_pushinteger(l, c.r);
    lua_pushinteger(l, c.g);
    lua_pushinteger(l, c.b);
    lua_pushinteger(l, c.a);
    return 4;
};

int L_RGBAToColor(lua_State *l)
{
    lua_Number r = ceil(luaL_optnumber(l, 1, 255));
    lua_Number g = ceil(luaL_optnumber(l, 2, 255));
    lua_Number b = ceil(luaL_optnumber(l, 3, 255));
    lua_Number a = ceil(luaL_optnumber(l, 4, 255));
    lua_pushinteger(l, (uint32_t)ColorToInt((Color){
        .r = (unsigned char)(r < 0 ? 0 : r > 255 ? 255 : r),
        .g = (unsigned char)(g < 0 ? 0 : g > 255 ? 255 : g),
        .b = (unsigned char)(b < 0 ? 0 : b > 255 ? 255 : b),
        .a = (unsigned char)(a < 0 ? 0 : a > 255 ? 255 : a),
    }));
    return 1;
};

// Audio device management functions TODO as needed
// // RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
// // RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
// l_func_0_1(IsAudioDeviceReady, boolean)                                  // Check if audio device has been initialized successfully
// l_func_1_0(SetMasterVolume, number)                             // Set master volume (listener)
// l_func_0_1(GetMasterVolume, number)                                    // Get master volume (listener)

// Wave/Sound loading/unloading functions
class_ctor_1(Sound, , LoadSound, IsSoundValid, string)
class_index_and_newindex(Sound)
class_gc(Sound, , UnloadSound)

// Wave/Sound management functions
class_func_0_0(Sound, , Play, PlaySound)
class_func_0_0(Sound, , Stop, StopSound)
class_func_0_0(Sound, , Pause, PauseSound)
class_func_0_0(Sound, , Resume, ResumeSound)
class_getterf(Sound, , boolean, Playing, IsSoundPlaying)
class_setterf(Sound, , number, Volume, SetSoundVolume)
class_setterf(Sound, , number, Pitch, SetSoundPitch)
class_setterf(Sound, , number, Pan, SetSoundPan)

// Music management functions
class_ctor_1(Music, , LoadMusicStream, IsMusicValid, string)
class_index_and_newindex(Music)
class_gc(Music, , UnloadMusicStream)
class_func_0_0(Music, , Play, PlayMusicStream)
class_func_0_0(Music, , Stop, StopMusicStream)
class_func_0_0(Music, , Update, UpdateMusicStream) // TODO make this automatic?
class_func_0_0(Music, , Pause, PauseMusicStream)
class_func_0_0(Music, , Resume, ResumeMusicStream)
class_getterf(Music, , boolean, Playing, IsMusicStreamPlaying)
class_setterf(Music, , number, Position, SeekMusicStream)
class_setterf(Music, , number, Volume, SetMusicVolume)
class_setterf(Music, , number, Pitch, SetMusicPitch)
class_setterf(Music, , number, Pan, SetMusicPan)
class_getterf(Music, , number, Length, GetMusicTimeLength)
class_getterf(Music, , number, Position, GetMusicTimePlayed)

l_global_funcs_luaopen(raylib_g,
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

    // Random values generation functions
    l_func_reg(SetRandomSeed),
    l_func_reg(GetRandomValue),
    l_func_reg(GetRandomSequence),

    // Misc. functions
    l_func_reg(TakeScreenshot),
    l_func_reg(OpenURL),

    l_func_reg(TraceLog),
    l_func_reg(SetTraceLogLevel),

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
    l_func_reg(ColorToRGBA),
    l_func_reg(RGBAToColor),

    // Wave/Sound loading/unloading functions
    l_func_reg(LoadSound),

    // Music management functions
    l_func_reg(LoadMusicStream)
)

class_luaopen(Sound,
    class_method_reg(Sound, __index),
    class_method_reg(Sound, __newindex),
    class_method_reg(Sound, __gc),
    class_method_reg(Sound, Play),
    class_method_reg(Sound, Stop),
    class_method_reg(Sound, Pause),
    class_method_reg(Sound, Resume),
    class_getter_reg(Sound, Playing),
    class_setter_reg(Sound, Volume),
    class_setter_reg(Sound, Pitch),
    class_setter_reg(Sound, Pan))

class_luaopen(Music,
    class_method_reg(Music, __index),
    class_method_reg(Music, __newindex),
    class_method_reg(Music, __gc),
    class_method_reg(Music, Play),
    class_method_reg(Music, Stop),
    class_method_reg(Music, Update),
    class_method_reg(Music, Pause),
    class_method_reg(Music, Resume),
    class_getter_reg(Music, Playing),
    class_setter_reg(Music, Position),
    class_setter_reg(Music, Volume),
    class_setter_reg(Music, Pitch),
    class_setter_reg(Music, Pan),
    class_getter_reg(Music, Length),
    class_getter_reg(Music, Position)
)

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

    lua_cpcall(l, luaopen_raylib_g, NULL);
    lua_cpcall(l, luaopen_Sound, NULL);
    lua_cpcall(l, luaopen_Music, NULL);
}