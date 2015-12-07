#ifndef MNG_NO_1_2_4BIT_SUPPORT
if ((pData->iJHDRalphacompression != MNG_COMPRESSION_DEFLATE     ) &&
        (pData->iJHDRalphacompression != MNG_COMPRESSION_BASELINEJPEG)    )
      MNG_ERROR (pData, MNG_INVALIDCOMPRESS);
