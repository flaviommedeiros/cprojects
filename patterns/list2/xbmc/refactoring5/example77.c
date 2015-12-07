#ifndef MNG_NO_DELTA_PNG
if ((pData->bHasDHDR) && (pData->bDeltaimmediate))
      pData->fStorerow = (mng_fptr)mng_delta_idx1;
    else
#endif
      pData->fStorerow = (mng_fptr)mng_store_idx1;
