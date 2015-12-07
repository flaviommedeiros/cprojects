#ifndef MNG_NO_16BIT_SUPPORT
if (bSourceRGBA16)
                          pData->fRetrieverow = (mng_fptr)mng_retrieve_ga16;
                        else
#endif
                          pData->fRetrieverow = (mng_fptr)mng_retrieve_ga8;
