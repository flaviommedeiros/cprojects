#ifndef MNG_NO_OPEN_CLOSE_STREAM
if (pData->fOpenstream && !pData->fOpenstream (hHandle))
    /* open it and start reading */
    iRetcode = MNG_APPIOERROR;
  else
#endif
    iRetcode = mng_read_graphic (pData);
