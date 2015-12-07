#ifndef MNG_NO_16BIT_SUPPORT
if (pBuf->iBitdepth > 8)
    {
      pData->fRetrieverow = (mng_fptr)mng_retrieve_rgba16;
      pData->fStorerow    = (mng_fptr)mng_store_rgba16;
    }
    else
#endif
    {
      pData->fRetrieverow = (mng_fptr)mng_retrieve_rgba8;
      pData->fStorerow    = (mng_fptr)mng_store_rgba8;
    }
