#ifdef HAVE_HEADSET
if(g_extern.console.sound.mode == SOUND_MODE_HEADSET)
      params.param_attrib = CELL_AUDIO_PORTATTR_OUT_SECONDARY;
   else
#endif
      params.param_attrib = 0;
