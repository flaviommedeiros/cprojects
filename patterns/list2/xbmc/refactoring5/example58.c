#ifndef MNG_NO_16BIT_SUPPORT
if (bTargetRGBA16)        /* abuse tiling routine to shift source-pixels */
               pData->fTilerow = (mng_fptr)mng_tile_rgba16;
             else
#endif
               pData->fTilerow = (mng_fptr)mng_tile_rgba8;
