#ifdef MNG_SUPPORT_DISPLAY
if ((!pData->bTimerset) && (!pData->bSectionwait) && (!pData->bEOF))
#else
  if (!pData->bEOF)
#endif
  {
    pData->iSuspendpoint = 0;            /* safely reset it here ! */
    pPush = pData->pFirstpushchunk;

    iRetcode = process_raw_chunk (pData, pPush->pData, pPush->iLength);
    if (iRetcode)
      return iRetcode;

#ifdef MNG_SUPPORT_DISPLAY             /* refresh needed ? */
    if ((!pData->bTimerset) && (!pData->bSuspended) && (pData->bNeedrefresh))
    {
      iRetcode = mng_display_progressive_refresh (pData, 1);
      if (iRetcode)                      /* on error bail out */
        return iRetcode;
    }
#endif
  }
