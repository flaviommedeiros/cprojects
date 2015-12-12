static music_module_t *music_modules[] =
{
#ifdef FEATURE_SOUND
    &music_sdl_module,
    &music_opl_module,
#endif
    NULL,
};
