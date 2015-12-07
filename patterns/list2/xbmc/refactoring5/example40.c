#ifdef MNG_SUPPORT_DYNAMICMNG
if (pData->bStopafterseek)           /* need to stop after this SEEK ? */
  {
    pData->bFreezing      = MNG_TRUE;  /* stop processing on this one */
    pData->bRunningevent  = MNG_FALSE;
    pData->bStopafterseek = MNG_FALSE;
    pData->bNeedrefresh   = MNG_TRUE;  /* make sure the last bit is displayed ! */
  }
  else
#endif
  {                                    /* restore the initial or SAVE state */
    mng_retcode iRetcode = restore_state (pData);

    if (iRetcode)                      /* on error bail out */
      return iRetcode;

#ifdef MNG_SUPPORT_DYNAMICMNG
                                       /* stop after next SEEK ? */
    if ((pData->bDynamic) || (pData->bRunningevent))
      pData->bStopafterseek = MNG_TRUE;
#endif
  }
