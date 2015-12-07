#ifndef MNG_NO_DELTA_PNG
if ((pData->bHasDHDR) && (pData->bDeltaimmediate))
      pData->fStorerow = (mng_fptr)mng_delta_ga16;
    else
#endif
      pData->fStorerow = (mng_fptr)mng_store_ga16;
