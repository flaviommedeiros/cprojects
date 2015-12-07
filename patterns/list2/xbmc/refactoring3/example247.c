switch (local_buf[0]) {
    case 'P' : return RC_LOAD_FILE;
    case 'U' : return RC_TOGGLE_PAUSE;
    case 'S' : return RC_QUIT;
    case 'N' : return RC_NEXT;
    case 'B' : return RC_REALLY_PREVIOUS;
    case 'R' : repeatflag=atoi(local_buf+2);return RC_NONE;
    case 'D' : randomflag=atoi(local_buf+2);return RC_QUIT;
    case 'L' : selectflag=atoi(local_buf+2);return RC_QUIT;
    case 'V' : *valp     =atoi(local_buf+2);return RC_CHANGE_VOLUME;
#ifdef SUPPORT_SOUNDSPEC
    case 'W' : return RC_TOGGLE_CTL_SPEANA;
#endif
    case 'Q' :
    default : exitflag=1;return RC_QUIT;
    }
