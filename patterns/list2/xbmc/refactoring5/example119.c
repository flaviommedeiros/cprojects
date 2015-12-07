#ifdef MNG_SUPPORT_READ
if (pData->bReading)             /* set during read&display ? */
      {
        if (pData->bSuspended)         /* calculate proper synchronization */
          pData->iSynctime = pData->iSynctime - pData->iSuspendtime +
                             pData->fGettickcount (hHandle);
        else
          pData->iSynctime = pData->fGettickcount (hHandle);

        pData->bSuspended = MNG_FALSE; /* now reset this flag */  
                                       /* and continue reading */
        iRetcode = mng_read_graphic (pData);

        if (pData->bEOF)               /* already at EOF ? */
        {
          pData->bReading = MNG_FALSE; /* then we're no longer reading */
                                       /* drop invalidly stored objects */
          mng_drop_invalid_objects (pData);
        }
      }
      else
#endif /* MNG_SUPPORT_READ */
      {                                /* synchronize timing */
        pData->iSynctime = pData->fGettickcount (hHandle);
                                       /* resume display processing */
        iRetcode = mng_process_display (pData);
      }
