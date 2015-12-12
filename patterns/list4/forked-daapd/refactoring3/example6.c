switch (ps->data_kind)
    {
      case DATA_KIND_HTTP:
	ret = transcode(audio_buf, len, ps->xcode, &icy_timer);

	if (icy_timer)
	  metadata_check_icy();
	break;

      case DATA_KIND_FILE:
	ret = transcode(audio_buf, len, ps->xcode, &icy_timer);
	break;

#ifdef HAVE_SPOTIFY_H
      case DATA_KIND_SPOTIFY:
	ret = spotify_audio_get(audio_buf, len);
	break;
#endif

      case DATA_KIND_PIPE:
	ret = pipe_audio_get(audio_buf, len);
	break;

      default:
	ret = -1;
    }
