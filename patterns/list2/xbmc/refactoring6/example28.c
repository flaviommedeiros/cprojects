if ((iRead != 0) ||            /* did we get an unexpected eof ? */
#ifdef MNG_INCLUDE_JNG
            (pData->bHasIHDR || pData->bHasMHDR || pData->bHasJHDR))
#else
            (pData->bHasIHDR || pData->bHasMHDR)
