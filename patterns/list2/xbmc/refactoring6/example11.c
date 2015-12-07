if (((pDescr->iMustNOThaves & MNG_DESCR_NOIHDR) && (pData->bHasIHDR)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOBASI) && (pData->bHasBASI)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NODHDR) && (pData->bHasDHDR)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOIDAT) && (pData->bHasIDAT)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOPLTE) && (pData->bHasPLTE)) ||
#ifdef MNG_INCLUDE_JNG
      ((pDescr->iMustNOThaves & MNG_DESCR_NOJHDR) && (pData->bHasJHDR)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOJDAT) && (pData->bHasJDAT)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOJDAA) && (pData->bHasJDAA)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOJSEP) && (pData->bHasJSEP)) ||
#endif
      ((pDescr->iMustNOThaves & MNG_DESCR_NOMHDR) && (pData->bHasMHDR)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOLOOP) && (pData->bHasLOOP)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOTERM) && (pData->bHasTERM)) ||
      ((pDescr->iMustNOThaves & MNG_DESCR_NOSAVE) && (pData->bHasSAVE))   )
    MNG_ERROR (pData, MNG_SEQUENCEERROR);
