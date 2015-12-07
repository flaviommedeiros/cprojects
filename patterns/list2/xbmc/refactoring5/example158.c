#ifdef MNG_INCLUDE_JNG
if (((mng_chunk_headerp)pChunk)->iChunkname == MNG_UINT_JHDR)
        pData->eImagetype     = mng_it_jng;
      else
#endif
        pData->eImagetype     = mng_it_mng;
