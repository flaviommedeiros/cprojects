#ifndef MNG_NO_16BIT_SUPPORT
if (bTargetRGBA16)
                         pData->fDeltarow = (mng_fptr)mng_composeunder_rgba16;
                       else
#endif
                         pData->fDeltarow = (mng_fptr)mng_composeunder_rgba8;
