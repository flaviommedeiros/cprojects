#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if ((iType != MNG_DELTATYPE_REPLACERGB) && (iType != MNG_DELTATYPE_DELTARGB))
#else
  if ((pData->iPPLTtype != MNG_DELTATYPE_REPLACERGB) &&
      (pData->iPPLTtype != MNG_DELTATYPE_DELTARGB  )    )
#endif
  {
    if (pBuf->bHasTRNS)
    {
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
      if (iCount > pBuf->iTRNScount)
        pBuf->iTRNScount = iCount;
#else
      if (pData->iPPLTcount > pBuf->iTRNScount)
        pBuf->iTRNScount = pData->iPPLTcount;
#endif
    }
    else
    {
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
      pBuf->iTRNScount = iCount;
      pBuf->bHasTRNS   = MNG_TRUE;
#else
      pBuf->iTRNScount = pData->iPPLTcount;
      pBuf->bHasTRNS   = MNG_TRUE;
#endif
    }
  }
