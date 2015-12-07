#ifndef MNG_OPTIMIZE_DISPLAYCALLS
if ((iType != MNG_DELTATYPE_REPLACEALPHA) && (iType != MNG_DELTATYPE_DELTAALPHA))
#else
  if ((pData->iPPLTtype != MNG_DELTATYPE_REPLACEALPHA) &&
      (pData->iPPLTtype != MNG_DELTATYPE_DELTAALPHA  )    )
#endif
  {
#ifndef MNG_OPTIMIZE_DISPLAYCALLS
    if (iCount > pBuf->iPLTEcount)
      pBuf->iPLTEcount = iCount;
#else
    if (pData->iPPLTcount > pBuf->iPLTEcount)
      pBuf->iPLTEcount = pData->iPPLTcount;
#endif
  }
