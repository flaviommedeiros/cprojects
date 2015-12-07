if ((((mng_uint32)pData->iChunkname & 0x20000000) == 0)
#ifdef MNG_SKIPCHUNK_SAVE
    && (pData->iChunkname != MNG_UINT_SAVE)
#endif
#ifdef MNG_SKIPCHUNK_SEEK
    && (pData->iChunkname != MNG_UINT_SEEK)
#endif
#ifdef MNG_SKIPCHUNK_DBYK
    && (pData->iChunkname != MNG_UINT_DBYK)
#endif
#ifdef MNG_SKIPCHUNK_ORDR
    && (pData->iChunkname != MNG_UINT_ORDR)
#endif
      )
    MNG_ERROR (pData, MNG_UNKNOWNCRITICAL);
