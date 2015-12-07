#ifdef MNG_INCLUDE_JNG
if (mng_get_uint32 (pData->pReadbuf) == JNG_SIG)
        pData->eSigtype = mng_it_jng;
      else
#endif
      if (mng_get_uint32 (pData->pReadbuf) == MNG_SIG)
        pData->eSigtype = mng_it_mng;
      else
        MNG_ERROR (pData, MNG_INVALIDSIG);
