#ifdef MNG_INCLUDE_JNG
if (pData->bHasJHDR)         /* is JNG alpha-channel ? */
          {                            /* just store in object ? */
            if ((!iRslt) && (pData->fStorerow))
              iRslt = ((mng_storerow)pData->fStorerow)     (pData);
          }
          else
#endif /* MNG_INCLUDE_JNG */
          {                            /* process this row */
            if ((!iRslt) && (pData->fProcessrow))
              iRslt = ((mng_processrow)pData->fProcessrow) (pData);
                                       /* store in object ? */
            if ((!iRslt) && (pData->fStorerow))
              iRslt = ((mng_storerow)pData->fStorerow)     (pData);
                                       /* color correction ? */
            if ((!iRslt) && (pData->fCorrectrow))
              iRslt = ((mng_correctrow)pData->fCorrectrow) (pData);
                                       /* slap onto canvas ? */
            if ((!iRslt) && (pData->fDisplayrow))
            {
              iRslt = ((mng_displayrow)pData->fDisplayrow) (pData);

              if (!iRslt)              /* check progressive display refresh */
                iRslt = mng_display_progressive_check (pData);

            }
          }
