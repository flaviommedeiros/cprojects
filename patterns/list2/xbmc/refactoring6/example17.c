if ((pData->iJHDRalphafilter != MNG_FILTER_ADAPTIVE ) &&
#if defined(FILTER192) && defined(FILTER193)
        (pData->iJHDRalphafilter != MNG_FILTER_DIFFERING) &&
        (pData->iJHDRalphafilter != MNG_FILTER_NOFILTER )    )
#else
#ifdef FILTER192
        (pData->iJHDRalphafilter != MNG_FILTER_DIFFERING)
