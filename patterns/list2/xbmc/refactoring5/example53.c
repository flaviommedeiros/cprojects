#ifndef MNG_NO_16BIT_SUPPORT
if (bTargetRGBA16)
                         pData->fFliprow = (mng_fptr)mng_flip_rgba16;
                       else
#endif
                         pData->fFliprow = (mng_fptr)mng_flip_rgba8;
