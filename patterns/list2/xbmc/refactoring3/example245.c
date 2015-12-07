switch(e->type)
    {
      case CTLE_NOW_LOADING:
	ctl_file_name((char *)e->v1);
	break;
      case CTLE_PLAY_START:
	ctl_total_time(e->v1);
	break;
      case CTLE_CURRENT_TIME:
	ctl_current_time((int)e->v1);
	break;
      #ifndef CFG_FOR_SF
      case CTLE_LYRIC:
	ctl_lyric((int)e->v1);
	break;
      #endif
    }
