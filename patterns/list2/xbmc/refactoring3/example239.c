switch(k)
	    {
#ifdef XK_Down
	      case XK_Up:
#endif /* XK_Up */
#ifdef XK_KP_Up
	      case XK_KP_Up:
#endif /* XK_KP_Up */
		nze++;
		break;

#ifdef XK_Down
	      case XK_Down:
#endif /* XK_Down */
#ifdef XK_KP_Down
	      case XK_KP_Down:
#endif /* XK_KP_Down */
		nze--;
		break;

#ifdef XK_Left
	      case XK_Left:
#endif /* XK_Left */
#ifdef XK_KP_Left
	      case XK_KP_Left:
#endif /* XK_KP_Left */
		soundspec_update_interval =
		    (int32)(soundspec_update_interval*1.1);
		break;

#ifdef XK_Right
	      case XK_Right:
#endif /* XK_Right */
#ifdef XK_KP_Right
	      case XK_KP_Right:
#endif /* XK_KP_Right */
		soundspec_update_interval =
		    (int32)(soundspec_update_interval/1.1);
		if(soundspec_update_interval < 0.01 * play_mode->rate)
		    soundspec_update_interval =
			(int32)(0.01 * play_mode->rate);
		break;
	    }
