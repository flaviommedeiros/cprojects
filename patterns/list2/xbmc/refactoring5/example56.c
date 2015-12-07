#ifndef MNG_NO_16BIT_SUPPORT
if (bTargetRGBA16)
                         pData->fDeltarow = (mng_fptr)mng_delta_rgba16_rgba16;
                       else
#endif
                         pData->fDeltarow = (mng_fptr)mng_delta_rgba8_rgba8;
