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
    reg_LoadSound,
    reg_LoadMusicStream
)

class_luaopen(Sound,
    reg_Sound___index,
    reg_Sound___newindex,
    reg_Sound___gc,
    reg_Sound_Play,
    reg_Sound_Stop,
    reg_Sound_Pause,
    reg_Sound_Resume,
    reg_Sound_getPlaying,
    reg_Sound_setVolume,
    reg_Sound_setPitch,
    reg_Sound_setPan)

class_luaopen(Music,
    reg_Music___index,
    reg_Music___newindex,
    reg_Music___gc,
    reg_Music_Play,
    reg_Music_Stop,
    reg_Music_Update,
    reg_Music_Pause,
    reg_Music_Resume,
    reg_Music_getPlaying,
    reg_Music_setPosition,
    reg_Music_setVolume,
    reg_Music_setPitch,
    reg_Music_setPan,
    reg_Music_getLength,
    reg_Music_getPosition
)

int luaopen_rlaudio(lua_State *l) {
    lua_cpcall(l, luaopen_rlaudio_g, NULL);
    lua_cpcall(l, luaopen_Sound, NULL);
    lua_cpcall(l, luaopen_Music, NULL);

    doc_class(Sound, "raylib Sound",
        doc_class_ctors(Sound, doc_LoadSound)
        doc_class_fields(Sound)
        doc_class_methods(Sound,
            doc_Sound_Play,
            doc_Sound_Stop,
            doc_Sound_Pause,
            doc_Sound_Resume))
    doc_class(Music, "raylib Music",
        doc_class_ctors(Music, doc_LoadMusicStream)
        doc_class_fields(Music)
        doc_class_methods(Music,
            doc_Music_Play,
            doc_Music_Stop,
            doc_Music_Update,
            doc_Music_Pause,
            doc_Music_Resume))
    doc_module(rlaudio, "raylib audio",
        doc_module_classes(Sound, Music)
        doc_module_constants()
        doc_module_funcs())
    return 0;
}