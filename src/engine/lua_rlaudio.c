#include <engine/lua.h>
#include <raylib.h>

// Audio device management functions TODO as needed
// // RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
// // RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
// lfunc_0_1(IsAudioDeviceReady, boolean)                                  // Check if audio device has been initialized successfully
// lfunc_1_0(SetMasterVolume, number)                             // Set master volume (listener)
// lfunc_0_1(GetMasterVolume, number)                                    // Get master volume (listener)

// Wave/Sound loading/unloading functions
lclass_ctor_1(Sound, , LoadSound, IsSoundValid, string)
lclass_index_and_newindex(Sound)
lclass_gc(Sound, , UnloadSound)

// Wave/Sound management functions
lclass_func_0_0(Sound, , Play, PlaySound)
lclass_func_0_0(Sound, , Stop, StopSound)
lclass_func_0_0(Sound, , Pause, PauseSound)
lclass_func_0_0(Sound, , Resume, ResumeSound)
lclass_getterf(Sound, , boolean, Playing, IsSoundPlaying)
lclass_setterf(Sound, , number, Volume, SetSoundVolume)
lclass_setterf(Sound, , number, Pitch, SetSoundPitch)
lclass_setterf(Sound, , number, Pan, SetSoundPan)

// Music management functions
lclass_ctor_1(Music, , LoadMusicStream, IsMusicValid, string)
lclass_index_and_newindex(Music)
lclass_gc(Music, , UnloadMusicStream)
lclass_func_0_0(Music, , Play, PlayMusicStream)
lclass_func_0_0(Music, , Stop, StopMusicStream)
lclass_func_0_0(Music, , Update, UpdateMusicStream) // TODO make this automatic?
lclass_func_0_0(Music, , Pause, PauseMusicStream)
lclass_func_0_0(Music, , Resume, ResumeMusicStream)
lclass_getterf(Music, , boolean, Playing, IsMusicStreamPlaying)
lclass_setterf(Music, , number, Position, SeekMusicStream)
lclass_setterf(Music, , number, Volume, SetMusicVolume)
lclass_setterf(Music, , number, Pitch, SetMusicPitch)
lclass_setterf(Music, , number, Pan, SetMusicPan)
lclass_getterf(Music, , number, Length, GetMusicTimeLength)
lclass_getterf(Music, , number, Position, GetMusicTimePlayed)

l_global_funcs_luaopen(rlaudio_g,
    // Wave/Sound loading/unloading functions
    lfunc_reg(LoadSound),

    // Music management functions
    lfunc_reg(LoadMusicStream)
)

lclass_luaopen(Sound,
    lclass_method_reg(Sound, __index),
    lclass_method_reg(Sound, __newindex),
    lclass_method_reg(Sound, __gc),
    lclass_method_reg(Sound, Play),
    lclass_method_reg(Sound, Stop),
    lclass_method_reg(Sound, Pause),
    lclass_method_reg(Sound, Resume),
    lclass_getter_reg(Sound, Playing),
    lclass_setter_reg(Sound, Volume),
    lclass_setter_reg(Sound, Pitch),
    lclass_setter_reg(Sound, Pan))

lclass_luaopen(Music,
    lclass_method_reg(Music, __index),
    lclass_method_reg(Music, __newindex),
    lclass_method_reg(Music, __gc),
    lclass_method_reg(Music, Play),
    lclass_method_reg(Music, Stop),
    lclass_method_reg(Music, Update),
    lclass_method_reg(Music, Pause),
    lclass_method_reg(Music, Resume),
    lclass_getter_reg(Music, Playing),
    lclass_setter_reg(Music, Position),
    lclass_setter_reg(Music, Volume),
    lclass_setter_reg(Music, Pitch),
    lclass_setter_reg(Music, Pan),
    lclass_getter_reg(Music, Length),
    lclass_getter_reg(Music, Position)
)

int luaopen_rlaudio(lua_State *l) {
    lua_cpcall(l, luaopen_rlaudio_g, NULL);
    lua_cpcall(l, luaopen_Sound, NULL);
    lua_cpcall(l, luaopen_Music, NULL);
    return 0;
}