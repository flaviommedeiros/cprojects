if ((pData->iFilter != MNG_FILTER_ADAPTIVE ) &&
#if defined(FILTER192) && defined(FILTER193)
      (pData->iFilter != MNG_FILTER_DIFFERING) &&
      (pData->iFilter != MNG_FILTER_NOFILTER )    )
#else
#ifdef FILTER192
      (pData->iFilter != MNG_FILTER_DIFFERING)
