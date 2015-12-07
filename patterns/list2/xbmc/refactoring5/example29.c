#ifndef MNG_NO_16BIT_SUPPORT
if (pImage->pImgbuf->iBitdepth > 8)
                        pData->fRetrieverow = (mng_fptr)mng_retrieve_rgb16;
                      else
#endif
                        pData->fRetrieverow = (mng_fptr)mng_retrieve_rgb8;
