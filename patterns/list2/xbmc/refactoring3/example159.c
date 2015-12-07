switch (pData->iBreakpoint)      /* return to broken display routine */
      {
#ifndef MNG_SKIPCHUNK_FRAM
        case  1 : { iRetcode = mng_process_display_fram2 (pData); break; }
#endif
        case  2 : { iRetcode = mng_process_display_ihdr  (pData); break; }
#ifndef MNG_SKIPCHUNK_SHOW
        case  3 : ;                     /* same as 4 !!! */
        case  4 : { iRetcode = mng_process_display_show  (pData); break; }
#endif
#ifndef MNG_SKIPCHUNK_CLON
        case  5 : { iRetcode = mng_process_display_clon2 (pData); break; }
#endif
#ifdef MNG_INCLUDE_JNG
        case  7 : { iRetcode = mng_process_display_jhdr  (pData); break; }
#endif
        case  6 : ;                     /* same as 8 !!! */
        case  8 : { iRetcode = mng_process_display_iend  (pData); break; }
#ifndef MNG_SKIPCHUNK_MAGN
        case  9 : { iRetcode = mng_process_display_magn2 (pData); break; }
#endif
        case 10 : { iRetcode = mng_process_display_mend2 (pData); break; }
#ifndef MNG_SKIPCHUNK_PAST
        case 11 : { iRetcode = mng_process_display_past2 (pData); break; }
#endif
      }
