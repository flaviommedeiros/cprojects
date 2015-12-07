#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* processing a delta-image ? */
      pImage = (mng_imagep)pData->pDeltaImage;
    else
#endif
      pImage = (mng_imagep)pData->pCurrentobj;
