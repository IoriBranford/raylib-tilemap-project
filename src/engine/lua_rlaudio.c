#include <engine/lua.h>
#include <raylib.h>

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

l_global_funcs_luaopen(rlaudio_g,
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

int luaopen_rlaudio(lua_State *l) {
    lua_cpcall(l, luaopen_rlaudio_g, NULL);
    lua_cpcall(l, luaopen_Sound, NULL);
    lua_cpcall(l, luaopen_Music, NULL);
}