if (                               /* display "on-the-fly" ? */
#ifndef MNG_SKIPCHUNK_MAGN
         (((mng_imagep)pData->pStoreobj)->iMAGN_MethodX == 0) &&
         (((mng_imagep)pData->pStoreobj)->iMAGN_MethodY == 0) &&
#endif
         ( (pData->eImagetype == mng_it_png         ) ||
           (((mng_imagep)pData->pStoreobj)->bVisible)    )       )
    {
      next_layer (pData);              /* that's a new layer then ! */

      if (pData->bTimerset)            /* timer break ? */
        pData->iBreakpoint = 2;
      else
      {
        pData->iBreakpoint = 0;
                                       /* anything to display ? */
        if ((pData->iDestr > pData->iDestl) && (pData->iDestb > pData->iDestt))
          set_display_routine (pData); /* then determine display routine */
      }
    }
