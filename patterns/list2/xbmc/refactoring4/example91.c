#ifdef MNG_SUPPORT_DISPLAY
if ((!pData->bTimerset) && (!pData->bSectionwait) && (!pData->bEOF))
#else
  if (!pData->bEOF)
#endif
  {
#ifdef MNG_SUPPORT_DISPLAY
                                       /* freezing in progress ? */
    if ((pData->bFreezing) && (pData->iSuspendpoint == 0))
      pData->bRunning = MNG_FALSE;     /* then this is the right moment to do it */
#endif

    if (pData->iSuspendpoint <= 2)
    {
      iBuflen  = sizeof (mng_uint32);  /* read length */
      iRetcode = read_databuffer (pData, pBuf, &pData->pReadbufnext, iBuflen, &iRead);

      if (iRetcode)                    /* bail on errors */
        return iRetcode;

      if (pData->bSuspended)           /* suspended ? */
        pData->iSuspendpoint = 2;
      else                             /* save the length */
      {
        pData->iChunklen = mng_get_uint32 (pBuf);
        if (pData->iChunklen > 0x7ffffff)
           return MNG_INVALIDLENGTH;
      }

    }

    if (!pData->bSuspended)            /* still going ? */
    {                                  /* previously suspended or not eof ? */
      if ((pData->iSuspendpoint > 2) || (iRead == iBuflen))
      {                                /* determine length chunkname + data (+ crc) */
        if (pData->iCrcmode & MNG_CRC_INPUT)
          iBuflen = pData->iChunklen + (mng_uint32)(sizeof (mng_chunkid) + sizeof (mng_uint32));
        else
          iBuflen = pData->iChunklen + (mng_uint32)(sizeof (mng_chunkid));

                                       /* do we have enough data in the current push buffer ? */
        if ((pData->pFirstpushdata) && (iBuflen <= pData->pFirstpushdata->iRemaining))
        {
          mng_pushdatap pPush  = pData->pFirstpushdata;
          pBuf                 = pPush->pDatanext;
          pPush->pDatanext    += iBuflen;
          pPush->iRemaining   -= iBuflen;
          pData->iSuspendpoint = 0;    /* safely reset this here ! */

          iRetcode = check_chunk_crc (pData, pBuf, iBuflen);
          if (iRetcode)
            return iRetcode;

          if (!pPush->iRemaining)      /* buffer depleted? then release it */
            iRetcode = mng_release_pushdata (pData);
        }
        else
        {
          if (iBuflen < iBufmax)       /* does it fit in default buffer ? */
          {                            /* note that we don't use the full size
                                          so there's always a zero-byte at the
                                          very end !!! */
            iRetcode = read_databuffer (pData, pBuf, &pData->pReadbufnext, iBuflen, &iRead);
            if (iRetcode)              /* bail on errors */
              return iRetcode;

            if (pData->bSuspended)     /* suspended ? */
              pData->iSuspendpoint = 3;
            else
            {
              if (iRead != iBuflen)    /* did we get all the data ? */
                MNG_ERROR (pData, MNG_UNEXPECTEDEOF);
              iRetcode = check_chunk_crc (pData, pBuf, iBuflen);
            }
          }
          else
          {
            if (iBuflen > 16777216)    /* is the length incredible? */
              MNG_ERROR (pData, MNG_IMPROBABLELENGTH);

            if (!pData->iSuspendpoint) /* create additional large buffer ? */
            {                          /* again reserve space for the last zero-byte */
              pData->iLargebufsize = iBuflen + 1;
              pData->pLargebufnext = MNG_NULL;
              MNG_ALLOC (pData, pData->pLargebuf, pData->iLargebufsize);
            }

            iRetcode = read_databuffer (pData, pData->pLargebuf, &pData->pLargebufnext, iBuflen, &iRead);
            if (iRetcode)
              return iRetcode;

            if (pData->bSuspended)     /* suspended ? */
              pData->iSuspendpoint = 4;
            else
            {
              if (iRead != iBuflen)    /* did we get all the data ? */
                MNG_ERROR (pData, MNG_UNEXPECTEDEOF);
              iRetcode = check_chunk_crc (pData, pData->pLargebuf, iBuflen);
                                       /* cleanup additional large buffer */
              MNG_FREE (pData, pData->pLargebuf, pData->iLargebufsize);
            }
          }
        }

        if (iRetcode)                  /* on error bail out */
          return iRetcode;

      }
      else
      {                                /* that's final */
        iRetcode = mng_process_eof (pData);

        if (iRetcode)                  /* on error bail out */
          return iRetcode;

        if ((iRead != 0) ||            /* did we get an unexpected eof ? */
#ifdef MNG_INCLUDE_JNG
            (pData->bHasIHDR || pData->bHasMHDR || pData->bHasJHDR))
#else
            (pData->bHasIHDR || pData->bHasMHDR))
#endif
          MNG_ERROR (pData, MNG_UNEXPECTEDEOF);
      } 
    }
