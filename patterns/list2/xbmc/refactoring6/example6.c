if (
#ifndef MNG_SKIPCHUNK_MAGN
         ( ((mng_imagep)pData->pStoreobj)->iMAGN_MethodX == 0) &&
         ( ((mng_imagep)pData->pStoreobj)->iMAGN_MethodY == 0) &&
#endif
         ( (pData->eImagetype == mng_it_jng         ) ||
           (((mng_imagep)pData->pStoreobj)->bVisible)    )       )
    {
      next_layer (pData);              /* that's a new layer then ! */

      pData->iBreakpoint = 0;

      if (pData->bTimerset)            /* timer break ? */
        pData->iBreakpoint = 7;
      else
      if (pData->bRunning)             /* still running ? */
      {                                /* anything to display ? */
        if ((pData->iDestr > pData->iDestl) && (pData->iDestb > pData->iDestt))
        {
          set_display_routine (pData); /* then determine display routine */
                                       /* display from the object we store in */
          pData->pRetrieveobj = pData->pStoreobj;
        }
      }
    }
