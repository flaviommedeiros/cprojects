switch (artwork)
    {
      case ARTWORK_NONE:
	break;
      case ARTWORK_UNKNOWN:
      case ARTWORK_OWN:
	if (cfg_getbool(cfg_getsec(cfg, "library"), "artwork_individual"))
	  ret = artwork_get_own_image(evbuf, in_path, max_w, max_h, out_path);
	break;
#ifdef HAVE_SPOTIFY_H
      case ARTWORK_SPOTIFY:
	ret = spotify_artwork_get(evbuf, in_path, max_w, max_h);
	(ret < 0) ? (ret = 0) : (ret = ART_FMT_JPEG);
	break;
#endif
#if LIBAVFORMAT_VERSION_MAJOR >= 55 || (LIBAVFORMAT_VERSION_MAJOR == 54 && LIBAVFORMAT_VERSION_MINOR >= 6)
      case ARTWORK_EMBEDDED:
	ret = artwork_get_embedded_image(evbuf, in_path, max_w, max_h);
	break;
#endif
      case ARTWORK_HTTP:
	ret = artwork_get_player_image(evbuf, in_path);
	break;
    }
