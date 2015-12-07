#ifndef MNG_NO_DELTA_PNG
if ((!bSourceRGBA16) && (bTargetRGBA16))
            pData->fScalerow = (mng_fptr)mng_scale_rgba8_rgba16;
          else
          if ((bSourceRGBA16) && (!bTargetRGBA16))
            pData->fScalerow = (mng_fptr)mng_scale_rgba16_rgba8;
          else
#endif
#endif
            pData->fScalerow = MNG_NULL;
