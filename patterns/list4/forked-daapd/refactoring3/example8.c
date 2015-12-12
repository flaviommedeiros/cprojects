switch (ps->data_kind)
    {
      case DATA_KIND_HTTP:
	ret = 0;
	break;

      case DATA_KIND_FILE:
	ret = transcode_seek(ps->xcode, seek_ms);
	break;

#ifdef HAVE_SPOTIFY_H
      case DATA_KIND_SPOTIFY:
	ret = spotify_playback_seek(seek_ms);
	break;
#endif

      case DATA_KIND_PIPE:
	ret = 0;
	break;

      default:
	ret = -1;
    }
