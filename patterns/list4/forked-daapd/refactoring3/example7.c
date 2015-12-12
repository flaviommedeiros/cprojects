switch (ps->data_kind)
    {
      case DATA_KIND_HTTP:
	ret = 0;
	break;

      case DATA_KIND_FILE:
	ret = 0;
	break;

#ifdef HAVE_SPOTIFY_H
      case DATA_KIND_SPOTIFY:
	ret = spotify_playback_pause();
	break;
#endif

      case DATA_KIND_PIPE:
	ret = 0;
	break;

      default:
	ret = -1;
    }
