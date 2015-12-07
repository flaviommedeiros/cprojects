switch(e->type)
    {
      case CTLE_NOW_LOADING:
	PanelReset();
	CanvasReset();
	CanvasClear();
	CanvasReadPanelInfo(1);
	CanvasUpdate(1);
	CanvasPaintAll();
	MPanelReset();
	MPanelReadPanelInfo(1);
	MPanelUpdateAll();
	MPanelPaintAll();
	MPanelStartLoad((char *)e->v1);
	break;
      case CTLE_LOADING_DONE:
	break;
      case CTLE_PLAY_START:
	w32g_ctle_play_start((int)e->v1 / play_mode->rate);
	break;
      case CTLE_PLAY_END:
	MainWndScrollbarProgressUpdate(-1);
	break;
      case CTLE_CURRENT_TIME: {
	  int sec;
	  if(midi_trace.flush_flag)
	      return;
	  if(ctl.trace_playing)
	      sec = (int)e->v1;
	  else
	  {
	      sec = current_trace_samples();
	      if(sec < 0)
		  sec = (int)e->v1;
	      else
		  sec = sec / play_mode->rate;
	  }
	  ctl_current_time(sec, (int)e->v2);
	  display_aq_ratio();
	  MainWndScrollbarProgressUpdate(sec);
	  ctl_panel_refresh();
	}
	break;
      case CTLE_NOTE:
	ctl_note((int)e->v1, (int)e->v2, (int)e->v3, (int)e->v4);
	break;
      case CTLE_GSLCD:
	ctl_gslcd((int)e->v1);
	CanvasReadPanelInfo(0);
	CanvasUpdate(0);
	CanvasPaint();
	break;
      case CTLE_MASTER_VOLUME:
	ctl_master_volume((int)e->v1);
	break;
	case CTLE_METRONOME:
		ctl_metronome((int) e->v1, (int) e->v2);
		break;
	case CTLE_KEYSIG:
		ctl_keysig((int8) e->v1, CTL_STATUS_UPDATE);
		break;
	case CTLE_KEY_OFFSET:
		ctl_keysig(CTL_STATUS_UPDATE, (int) e->v1);
		break;
	case CTLE_TEMPO:
		ctl_tempo((int) e->v1, CTL_STATUS_UPDATE);
		break;
	case CTLE_TIME_RATIO:
		ctl_tempo(CTL_STATUS_UPDATE, (int) e->v1);
		break;
      case CTLE_PROGRAM:
//	ctl_program((int)e->v1, (int)e->v2, (char *)e->v3);
	ctl_program((int)e->v1, (int)e->v2);
	break;
      case CTLE_VOLUME:
	ctl_volume((int)e->v1, (int)e->v2);
	break;
      case CTLE_EXPRESSION:
	ctl_expression((int)e->v1, (int)e->v2);
	break;
      case CTLE_PANNING:
	ctl_panning((int)e->v1, (int)e->v2);
	break;
      case CTLE_SUSTAIN:
	ctl_sustain((int)e->v1, (int)e->v2);
	break;
      case CTLE_PITCH_BEND:
	ctl_pitch_bend((int)e->v1, (int)e->v2);
	break;
      case CTLE_MOD_WHEEL:
	ctl_pitch_bend((int)e->v1, e->v2 ? -2 : 0x2000);
	break;
      case CTLE_CHORUS_EFFECT:
	break;
      case CTLE_REVERB_EFFECT:
	break;
#if 1
      case CTLE_LYRIC:
		  {
			char *lyric;
		    lyric = event2string((uint16)e->v1);
			if(lyric != NULL){
				MPanelMessageClearAll();
				MPanelMessageAdd(lyric+1,20000,1);
			}
		  }
#else
	default_ctl_lyric((uint16)e->v1);
#endif
	break;
	case CTLE_REFRESH:
		if (CanvasGetMode() == CANVAS_MODE_KBD_A
				|| CanvasGetMode() == CANVAS_MODE_KBD_B) {
			CanvasReadPanelInfo(0);
			CanvasUpdate(0);
			CanvasPaint();
		}
		break;
      case CTLE_RESET:
	ctl_reset();
	break;
      case CTLE_SPEANA:
	break;
      case CTLE_PAUSE:
	if(w32g_play_active)
	{
	    MainWndScrollbarProgressUpdate((int)e->v2);
	    if(!(int)e->v1)
		ctl_reset();
	    ctl_current_time((int)e->v2, 0);
	    ctl_panel_refresh();
	}
	break;
      case CTLE_MAXVOICES:
	ctl_maxvoices((int)e->v1);
	break;
    }
