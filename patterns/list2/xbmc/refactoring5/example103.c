#ifndef MNG_NO_16BIT_SUPPORT
if (iBitdepth == 16)
        pData->fPromoterow = (mng_fptr)mng_promote_g8_rgb16;
      else
#endif
        pData->fPromoterow = (mng_fptr)mng_promote_g8_rgb8;
