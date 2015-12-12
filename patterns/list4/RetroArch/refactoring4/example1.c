#ifdef HAVE_BB10
if (snd_pcm_playback_pause(alsa->pcm) == 0)
#else
      if (snd_pcm_plugin_flush(alsa->pcm, SND_PCM_CHANNEL_PLAYBACK) == 0)
#endif
      {
         alsa->is_paused = true;
         return true;
      }
      else
         return false;
