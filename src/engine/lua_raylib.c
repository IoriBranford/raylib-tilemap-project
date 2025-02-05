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
// lfunc_3_0(InitWindow, integer, integer, string) //(int width, int height, const char *title);  // Initialize window and OpenGL context
// lfunc_0_0(CloseWindow)                                     // Close window and unload OpenGL context
// lfunc_0_0(WindowShouldClose)                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
// lfunc_0_0(IsWindowReady)                                   // Check if window has been initialized successfully
// lfunc_0_0(IsWindowFullscreen)                              // Check if window is currently fullscreen
// lfunc_0_0(IsWindowHidden)                                  // Check if window is currently hidden
// lfunc_0_0(IsWindowMinimized)                               // Check if window is currently minimized
// lfunc_0_0(IsWindowMaximized)                               // Check if window is currently maximized
// lfunc_0_0(IsWindowFocused)                                 // Check if window is currently focused
// lfunc_0_0(IsWindowResized)                                 // Check if window has been resized last frame
// lfunc_1_0(IsWindowState, integer)                      // Check if one specific window flag is enabled
// lfunc_1_0(SetWindowState, integer)                    // Set window configuration state using flags
// lfunc_1_0(ClearWindowState, integer)                  // Clear window configuration state flags
// lfunc_0_0(ToggleFullscreen)                                // Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
// lfunc_0_0(ToggleBorderlessWindowed)                        // Toggle window state: borderless windowed, resizes window to match monitor resolution
// lfunc_0_0(MaximizeWindow)                                  // Set window state: maximized, if resizable
// lfunc_0_0(MinimizeWindow)                                  // Set window state: minimized, if resizable
// lfunc_0_0(RestoreWindow)                                   // Set window state: not minimized/maximized
// // TODO after Image class
// // lfunc_ud_0(SetWindowIcon, Image)                            // Set icon for window (single image, RGBA 32bit)
// // lfunc_ud1_0(SetWindowIcons, Image, integer)              // Set icon for window (multiple images, RGBA 32bit)
// lfunc_1_0(SetWindowTitle, string)                     // Set title for window
// lfunc_2_0(SetWindowPosition, integer, integer)                       // Set window position on screen
// lfunc_1_0(SetWindowMonitor, integer)                         // Set monitor for the current window
// lfunc_2_0(SetWindowMinSize, integer, integer)               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
// lfunc_2_0(SetWindowMaxSize, integer, integer)               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
// lfunc_2_0(SetWindowSize, integer, integer)                  // Set window dimensions
// lfunc_1_0(SetWindowOpacity, number)                       // Set window opacity [0.0f..1.0f]
// lfunc_0_0(SetWindowFocused)                                // Set window focused
// // RLAPI void *GetWindowHandle(void);                                // Get native window handle
// lfunc_0_1(GetScreenWidth, integer)                                   // Get current screen width
// lfunc_0_1(GetScreenHeight, integer)                                  // Get current screen height
// lfunc_0_1(GetRenderWidth, integer)                                   // Get current render width (it considers HiDPI)
// lfunc_0_1(GetRenderHeight, integer)                                  // Get current render height (it considers HiDPI)
// lfunc_0_1(GetMonitorCount, integer)                                  // Get number of connected monitors
// lfunc_0_1(GetCurrentMonitor, integer)                                // Get current monitor where window is placed
// lfunc_1_vec2(GetMonitorPosition, integer, Vector2);                    // Get specified monitor position
// lfunc_1_1(GetMonitorWidth, integer, integer)                           // Get specified monitor width (current video mode used by monitor)
// lfunc_1_1(GetMonitorHeight, integer, integer)                          // Get specified monitor height (current video mode used by monitor)
// lfunc_1_1(GetMonitorPhysicalWidth, integer, integer)                   // Get specified monitor physical width in millimetres
// lfunc_1_1(GetMonitorPhysicalHeight, integer, integer)                  // Get specified monitor physical height in millimetres
// lfunc_1_1(GetMonitorRefreshRate, integer, integer)                     // Get specified monitor refresh rate
// lfunc_0_vec2(GetWindowPosition, Vector2)                            // Get window position XY on monitor
// lfunc_0_vec2(GetWindowScaleDPI, Vector2)                            // Get window scale DPI factor
// lfunc_1_1(GetMonitorName, integer, string)                    // Get the human-readable, UTF-8 encoded name of the specified monitor
// lfunc_1_0(SetClipboardText, string)                    // Set clipboard text content
// lfunc_0_1(GetClipboardText, string)                         // Get clipboard text content
// // RLAPI Image GetClipboardImage(void);                              // Get clipboard image content
// // RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
// // RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling

// Cursor-related functions
lfunc_0_0(ShowCursor)
lfunc_0_0(HideCursor)
lfunc_0_0(IsCursorHidden)
lfunc_0_0(EnableCursor)
lfunc_0_0(DisableCursor)
lfunc_0_0(IsCursorOnScreen)

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
lfunc_1_0(SetTargetFPS, integer)
lfunc_0_1(GetFrameTime, number)
lfunc_0_1(GetTime, number)
lfunc_0_1(GetFPS, integer)

// Custom frame control functions probably will stay on C side

// Random values generation functions
lfunc_1_0(SetRandomSeed, integer)                      // Set the seed for the random number generator
lfunc_2_1(GetRandomValue, integer, integer, integer)                       // Get a random value between min and max (both included)

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
lfunc_1_0(TakeScreenshot, string)
// RLAPI void SetConfigFlags(unsigned int flags); necessary?
lfunc_1_0(OpenURL, string)

lfunc_2_0(TraceLog, integer, string)         // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
lfunc_1_0(SetTraceLogLevel, integer)                        // Set the current threshold (minimum) log level

// Files management functions
// File system functions
// Compression/Encoding functionality
// TODO as needed

// Color/pixel related functions
lfunc_3_Color(ColorFromHSV, number, number, number)

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

l_global_funcs_luaopen(raylib_g,
    // Cursor-related functions
    lfunc_reg(ShowCursor),
    lfunc_reg(HideCursor),
    lfunc_reg(IsCursorHidden),
    lfunc_reg(EnableCursor),
    lfunc_reg(DisableCursor),
    lfunc_reg(IsCursorOnScreen),

    // Timing-related functions
    lfunc_reg(SetTargetFPS),
    lfunc_reg(GetFrameTime),
    lfunc_reg(GetTime),
    lfunc_reg(GetFPS),

    // Random values generation functions
    lfunc_reg(SetRandomSeed),
    lfunc_reg(GetRandomValue),
    lfunc_reg(GetRandomSequence),

    // Misc. functions
    lfunc_reg(TakeScreenshot),
    lfunc_reg(OpenURL),

    lfunc_reg(TraceLog),
    lfunc_reg(SetTraceLogLevel),

    // Color/pixel related functions
    lfunc_reg(ColorFromHSV),
    lfunc_reg(ColorToRGBA),
    lfunc_reg(RGBAToColor)
)

int luaopen_rlinput(lua_State *l);
int luaopen_rlaudio(lua_State *l);

int luaopen_raylib(lua_State *l) {
    lua_cpcall(l, luaopen_raylib_g, NULL);
    lua_cpcall(l, luaopen_rlinput, NULL);
    lua_cpcall(l, luaopen_rlaudio, NULL);
    return 0;
}