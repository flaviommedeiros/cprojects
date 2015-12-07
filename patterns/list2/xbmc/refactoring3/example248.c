switch(e->type)
    {
    case CTLE_PLAY_START:
      ctl_total_time((int)e->v1);
      break;
    case CTLE_CURRENT_TIME:
      ctl_current_time((int)e->v1, (int)e->v2);
      break;
    case CTLE_MASTER_VOLUME:
      ctl_master_volume((int)e->v1);
      break;
    case CTLE_LYRIC:
      ctl_lyric((int)e->v1);
      break;
#ifdef SUPPORT_SOUNDSPEC
    case CTLE_SPEANA:
      ctl_speana_data((double *)e->v1, (int)e->v2);
    break;
#endif /* SUPPORT_SOUNDSPEC */

    }
