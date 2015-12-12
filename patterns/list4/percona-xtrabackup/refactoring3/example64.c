switch (sig) {
    case SIGINT:
    case SIGQUIT:
    case SIGTERM:
    case SIGHUP:
      printf("Aborting nicely\n");
      end_thr_alarm(0);
      break;
#ifdef SIGTSTP
    case SIGTSTP:
      printf("Aborting\n");
      exit(1);
      return 0;					/* Keep some compilers happy */
#endif
#ifdef USE_ONE_SIGNAL_HAND
     case THR_SERVER_ALARM:
       process_alarm(sig);
      break;
#endif
    }
