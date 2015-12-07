switch (pData->iBreakpoint)      /* return to broken display routine */
      {
#ifndef MNG_SKIPCHUNK_FRAM
        case  1 : { iRetcode = mng_process_display_fram2 (pData); break; }
#endif
#ifndef MNG_SKIPCHUNK_SHOW
        case  3 : ;                    /* same as 4 !!! */
        case  4 : { iRetcode = mng_process_display_show  (pData); break; }
#endif
#ifndef MNG_SKIPCHUNK_CLON
        case  5 : { iRetcode = mng_process_display_clon2 (pData); break; }
#endif
#ifndef MNG_SKIPCHUNK_MAGN
        case  9 : { iRetcode = mng_process_display_magn2 (pData); break; }
        case 10 : { iRetcode = mng_process_display_mend2 (pData); break; }
#endif
#ifndef MNG_SKIPCHUNK_PAST
        case 11 : { iRetcode = mng_process_display_past2 (pData); break; }
#endif
        default : MNG_ERROR (pData, MNG_INTERNALERROR);
      }
