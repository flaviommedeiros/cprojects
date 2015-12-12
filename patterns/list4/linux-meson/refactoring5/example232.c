#ifdef _IS_WINDOWS_
if (wMaxLen>1)                          // we need space for terminating 0
    {
        BOOL bLineToGet;                    // true when a line to get
        long lTimeOutTicks = U14WhenToTimeOut(hand);
        do
            bLineToGet = (BOOL)(U14LineCount(hand) != 0);
        while (!bLineToGet && !U14PassedTime(lTimeOutTicks));

        if (!bLineToGet)             /* Last-ditch attempt to avoid timeout */
        {           /* This can happen with anti-virus or network activity! */
            int i;
            for (i = 0; (i < 4) && (!bLineToGet); ++i)
            {
                Sleep(25);       /* Give other threads a chance for a while */
                bLineToGet = (BOOL)(U14LineCount(hand) != 0);
            }
        }

        if (bLineToGet)
        {
            if (asLastRetCode[hand] == U14ERR_NOERROR)     /* all ok so far */
            {
                DWORD       dwBytes = 0;
                *((WORD *)pBuffer) = wMaxLen;       /* set up length */
#ifndef _WIN64
                if (!USE_NT_DIOC(hand))             /* Win 95 DIOC here ? */
                {
                    char tstr[MAXSTRLEN+5];         /* Buffer for Win95 chars */
                    int iOK;

                    if (wMaxLen > MAXSTRLEN)        /* Truncate length */
                        wMaxLen = MAXSTRLEN;    

                    *((WORD *)tstr) = wMaxLen;      /* set len */

                    iOK = DeviceIoControl(aHand1401[hand],(DWORD)U14_GETSTRING,
                                    NULL, 0, tstr, wMaxLen+sizeof(short),
                                    &dwBytes, NULL);
                    if (iOK)                        /* Device IO control OK ? */
                    {
                        if (dwBytes >= 0)           /* If driver OK */
                        {
                            strcpy(pBuffer, tstr);
                            sErr = U14ERR_NOERROR;
                        }
                        else
                            sErr = U14ERR_DRIVCOMMS;
                    }
                    else
                    {
                        sErr = (short)GetLastError();
                        if (sErr > 0)               /* Errors are -ve */
                            sErr = (short)-sErr;
                    }
                }
                else
#endif
                {       /* Here for NT, the DLL must own the buffer */
                    HANDLE hMem = GlobalAlloc(GMEM_MOVEABLE,wMaxLen+sizeof(short));
                    if (hMem)
                    {
                        char* pMem = (char*)GlobalLock(hMem);
                        if (pMem)
                        {
                            int iOK = DeviceIoControl(aHand1401[hand],(DWORD)U14_GETSTRING,
                                            NULL, 0, pMem, wMaxLen+sizeof(short),
                                            &dwBytes, NULL);
                            if (iOK)                /* Device IO control OK ? */
                            {
                                if (dwBytes >= wMaxLen)
                                {
                                    strcpy(pBuffer, pMem+sizeof(short));
                                    sErr = *((SHORT*)pMem);
                                }
                                else
                                    sErr = U14ERR_DRIVCOMMS;
                            }
                            else
                                sErr = U14ERR_DRIVCOMMS;

                            GlobalUnlock(hMem);
                        }
                        else
                            sErr = U14ERR_OUTOFMEMORY;

                        GlobalFree(hMem);
                    }
                    else
                        sErr = U14ERR_OUTOFMEMORY;
                }

                if (sErr == U14ERR_NOERROR)     // If all OK...
                    TranslateString(pBuffer);   // ...convert any commas to spaces
                else                            // If we have had a comms error...
                    U14ForceReset(hand);        // ...make sure we get real reset

            }
            else
                sErr = asLastRetCode[hand];
        }
        else
        {
            sErr = U14ERR_TIMEOUT;
            U14ForceReset(hand);            //  make sure we get real reset
        }
    }
    else
        sErr = U14ERR_BUFF_SMALL;
