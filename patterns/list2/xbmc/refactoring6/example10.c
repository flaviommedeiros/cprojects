if (((pDescr->iMusthaves & MNG_DESCR_IHDR) && (!pData->bHasIHDR)) ||
#ifdef MNG_INCLUDE_JNG
      ((pDescr->iMusthaves & MNG_DESCR_JHDR) && (!pData->bHasJHDR)) ||
#endif
      ((pDescr->iMusthaves & MNG_DESCR_DHDR) && (!pData->bHasDHDR)) ||
      ((pDescr->iMusthaves & MNG_DESCR_LOOP) && (!pData->bHasLOOP)) ||
      ((pDescr->iMusthaves & MNG_DESCR_PLTE) && (!pData->bHasPLTE)) ||
      ((pDescr->iMusthaves & MNG_DESCR_MHDR) && (!pData->bHasMHDR)) ||
      ((pDescr->iMusthaves & MNG_DESCR_SAVE) && (!pData->bHasSAVE))   )
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
