const SDL_AudioTypeFilters sdl_audio_type_filters[] =
{
#if !NO_CONVERTERS
    { AUDIO_U8, AUDIO_S8, SDL_Convert_U8_to_S8 },
    { AUDIO_U8, AUDIO_U16LSB, SDL_Convert_U8_to_U16LSB },
    { AUDIO_U8, AUDIO_S16LSB, SDL_Convert_U8_to_S16LSB },
    { AUDIO_U8, AUDIO_U16MSB, SDL_Convert_U8_to_U16MSB },
    { AUDIO_U8, AUDIO_S16MSB, SDL_Convert_U8_to_S16MSB },
    { AUDIO_U8, AUDIO_S32LSB, SDL_Convert_U8_to_S32LSB },
    { AUDIO_U8, AUDIO_S32MSB, SDL_Convert_U8_to_S32MSB },
    { AUDIO_U8, AUDIO_F32LSB, SDL_Convert_U8_to_F32LSB },
    { AUDIO_U8, AUDIO_F32MSB, SDL_Convert_U8_to_F32MSB },
    { AUDIO_S8, AUDIO_U8, SDL_Convert_S8_to_U8 },
    { AUDIO_S8, AUDIO_U16LSB, SDL_Convert_S8_to_U16LSB },
    { AUDIO_S8, AUDIO_S16LSB, SDL_Convert_S8_to_S16LSB },
    { AUDIO_S8, AUDIO_U16MSB, SDL_Convert_S8_to_U16MSB },
    { AUDIO_S8, AUDIO_S16MSB, SDL_Convert_S8_to_S16MSB },
    { AUDIO_S8, AUDIO_S32LSB, SDL_Convert_S8_to_S32LSB },
    { AUDIO_S8, AUDIO_S32MSB, SDL_Convert_S8_to_S32MSB },
    { AUDIO_S8, AUDIO_F32LSB, SDL_Convert_S8_to_F32LSB },
    { AUDIO_S8, AUDIO_F32MSB, SDL_Convert_S8_to_F32MSB },
    { AUDIO_U16LSB, AUDIO_U8, SDL_Convert_U16LSB_to_U8 },
    { AUDIO_U16LSB, AUDIO_S8, SDL_Convert_U16LSB_to_S8 },
    { AUDIO_U16LSB, AUDIO_S16LSB, SDL_Convert_U16LSB_to_S16LSB },
    { AUDIO_U16LSB, AUDIO_U16MSB, SDL_Convert_U16LSB_to_U16MSB },
    { AUDIO_U16LSB, AUDIO_S16MSB, SDL_Convert_U16LSB_to_S16MSB },
    { AUDIO_U16LSB, AUDIO_S32LSB, SDL_Convert_U16LSB_to_S32LSB },
    { AUDIO_U16LSB, AUDIO_S32MSB, SDL_Convert_U16LSB_to_S32MSB },
    { AUDIO_U16LSB, AUDIO_F32LSB, SDL_Convert_U16LSB_to_F32LSB },
    { AUDIO_U16LSB, AUDIO_F32MSB, SDL_Convert_U16LSB_to_F32MSB },
    { AUDIO_S16LSB, AUDIO_U8, SDL_Convert_S16LSB_to_U8 },
    { AUDIO_S16LSB, AUDIO_S8, SDL_Convert_S16LSB_to_S8 },
    { AUDIO_S16LSB, AUDIO_U16LSB, SDL_Convert_S16LSB_to_U16LSB },
    { AUDIO_S16LSB, AUDIO_U16MSB, SDL_Convert_S16LSB_to_U16MSB },
    { AUDIO_S16LSB, AUDIO_S16MSB, SDL_Convert_S16LSB_to_S16MSB },
    { AUDIO_S16LSB, AUDIO_S32LSB, SDL_Convert_S16LSB_to_S32LSB },
    { AUDIO_S16LSB, AUDIO_S32MSB, SDL_Convert_S16LSB_to_S32MSB },
    { AUDIO_S16LSB, AUDIO_F32LSB, SDL_Convert_S16LSB_to_F32LSB },
    { AUDIO_S16LSB, AUDIO_F32MSB, SDL_Convert_S16LSB_to_F32MSB },
    { AUDIO_U16MSB, AUDIO_U8, SDL_Convert_U16MSB_to_U8 },
    { AUDIO_U16MSB, AUDIO_S8, SDL_Convert_U16MSB_to_S8 },
    { AUDIO_U16MSB, AUDIO_U16LSB, SDL_Convert_U16MSB_to_U16LSB },
    { AUDIO_U16MSB, AUDIO_S16LSB, SDL_Convert_U16MSB_to_S16LSB },
    { AUDIO_U16MSB, AUDIO_S16MSB, SDL_Convert_U16MSB_to_S16MSB },
    { AUDIO_U16MSB, AUDIO_S32LSB, SDL_Convert_U16MSB_to_S32LSB },
    { AUDIO_U16MSB, AUDIO_S32MSB, SDL_Convert_U16MSB_to_S32MSB },
    { AUDIO_U16MSB, AUDIO_F32LSB, SDL_Convert_U16MSB_to_F32LSB },
    { AUDIO_U16MSB, AUDIO_F32MSB, SDL_Convert_U16MSB_to_F32MSB },
    { AUDIO_S16MSB, AUDIO_U8, SDL_Convert_S16MSB_to_U8 },
    { AUDIO_S16MSB, AUDIO_S8, SDL_Convert_S16MSB_to_S8 },
    { AUDIO_S16MSB, AUDIO_U16LSB, SDL_Convert_S16MSB_to_U16LSB },
    { AUDIO_S16MSB, AUDIO_S16LSB, SDL_Convert_S16MSB_to_S16LSB },
    { AUDIO_S16MSB, AUDIO_U16MSB, SDL_Convert_S16MSB_to_U16MSB },
    { AUDIO_S16MSB, AUDIO_S32LSB, SDL_Convert_S16MSB_to_S32LSB },
    { AUDIO_S16MSB, AUDIO_S32MSB, SDL_Convert_S16MSB_to_S32MSB },
    { AUDIO_S16MSB, AUDIO_F32LSB, SDL_Convert_S16MSB_to_F32LSB },
    { AUDIO_S16MSB, AUDIO_F32MSB, SDL_Convert_S16MSB_to_F32MSB },
    { AUDIO_S32LSB, AUDIO_U8, SDL_Convert_S32LSB_to_U8 },
    { AUDIO_S32LSB, AUDIO_S8, SDL_Convert_S32LSB_to_S8 },
    { AUDIO_S32LSB, AUDIO_U16LSB, SDL_Convert_S32LSB_to_U16LSB },
    { AUDIO_S32LSB, AUDIO_S16LSB, SDL_Convert_S32LSB_to_S16LSB },
    { AUDIO_S32LSB, AUDIO_U16MSB, SDL_Convert_S32LSB_to_U16MSB },
    { AUDIO_S32LSB, AUDIO_S16MSB, SDL_Convert_S32LSB_to_S16MSB },
    { AUDIO_S32LSB, AUDIO_S32MSB, SDL_Convert_S32LSB_to_S32MSB },
    { AUDIO_S32LSB, AUDIO_F32LSB, SDL_Convert_S32LSB_to_F32LSB },
    { AUDIO_S32LSB, AUDIO_F32MSB, SDL_Convert_S32LSB_to_F32MSB },
    { AUDIO_S32MSB, AUDIO_U8, SDL_Convert_S32MSB_to_U8 },
    { AUDIO_S32MSB, AUDIO_S8, SDL_Convert_S32MSB_to_S8 },
    { AUDIO_S32MSB, AUDIO_U16LSB, SDL_Convert_S32MSB_to_U16LSB },
    { AUDIO_S32MSB, AUDIO_S16LSB, SDL_Convert_S32MSB_to_S16LSB },
    { AUDIO_S32MSB, AUDIO_U16MSB, SDL_Convert_S32MSB_to_U16MSB },
    { AUDIO_S32MSB, AUDIO_S16MSB, SDL_Convert_S32MSB_to_S16MSB },
    { AUDIO_S32MSB, AUDIO_S32LSB, SDL_Convert_S32MSB_to_S32LSB },
    { AUDIO_S32MSB, AUDIO_F32LSB, SDL_Convert_S32MSB_to_F32LSB },
    { AUDIO_S32MSB, AUDIO_F32MSB, SDL_Convert_S32MSB_to_F32MSB },
    { AUDIO_F32LSB, AUDIO_U8, SDL_Convert_F32LSB_to_U8 },
    { AUDIO_F32LSB, AUDIO_S8, SDL_Convert_F32LSB_to_S8 },
    { AUDIO_F32LSB, AUDIO_U16LSB, SDL_Convert_F32LSB_to_U16LSB },
    { AUDIO_F32LSB, AUDIO_S16LSB, SDL_Convert_F32LSB_to_S16LSB },
    { AUDIO_F32LSB, AUDIO_U16MSB, SDL_Convert_F32LSB_to_U16MSB },
    { AUDIO_F32LSB, AUDIO_S16MSB, SDL_Convert_F32LSB_to_S16MSB },
    { AUDIO_F32LSB, AUDIO_S32LSB, SDL_Convert_F32LSB_to_S32LSB },
    { AUDIO_F32LSB, AUDIO_S32MSB, SDL_Convert_F32LSB_to_S32MSB },
    { AUDIO_F32LSB, AUDIO_F32MSB, SDL_Convert_F32LSB_to_F32MSB },
    { AUDIO_F32MSB, AUDIO_U8, SDL_Convert_F32MSB_to_U8 },
    { AUDIO_F32MSB, AUDIO_S8, SDL_Convert_F32MSB_to_S8 },
    { AUDIO_F32MSB, AUDIO_U16LSB, SDL_Convert_F32MSB_to_U16LSB },
    { AUDIO_F32MSB, AUDIO_S16LSB, SDL_Convert_F32MSB_to_S16LSB },
    { AUDIO_F32MSB, AUDIO_U16MSB, SDL_Convert_F32MSB_to_U16MSB },
    { AUDIO_F32MSB, AUDIO_S16MSB, SDL_Convert_F32MSB_to_S16MSB },
    { AUDIO_F32MSB, AUDIO_S32LSB, SDL_Convert_F32MSB_to_S32LSB },
    { AUDIO_F32MSB, AUDIO_S32MSB, SDL_Convert_F32MSB_to_S32MSB },
    { AUDIO_F32MSB, AUDIO_F32LSB, SDL_Convert_F32MSB_to_F32LSB },
#endif  /* !NO_CONVERTERS */
    { 0, 0, NULL }
};