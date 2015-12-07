if ((pDescr->iMusthaves & MNG_DESCR_GenHDR) &&
#ifdef MNG_INCLUDE_JNG
        (!pData->bHasIHDR) && (!pData->bHasBASI) && (!pData->bHasDHDR) && (!pData->bHasJHDR))
#else
        (!pData->bHasIHDR) && (!pData->bHasBASI) && (!pData->bHasDHDR)
