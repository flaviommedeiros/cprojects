#ifndef MNG_NO_DELTA_PNG
if (pData->bHasDHDR)               /* update delta image ? */
      pImage = (mng_imagep)pData->pObjzero;
    else
#endif
    {
      pImage = (mng_imagep)pData->pCurrentobj;
      if (!pImage)                     /* no object then dump it in obj 0 */
        pImage = (mng_imagep)pData->pObjzero;
    }
