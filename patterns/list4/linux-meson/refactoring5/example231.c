#ifndef _WIN64
if (!USE_NT_DIOC(hand))             /* Using WIN 95 driver access? */
                {
                    int iOK = DeviceIoControl(aHand1401[hand], (DWORD)U14_SENDSTRING,
                                    NULL, 0, tstr, nChars,
                                    &dwBytes, NULL);
                    if (iOK)
                        sErr = (dwBytes >= (DWORD)nChars) ? U14ERR_NOERROR : U14ERR_DRIVCOMMS;
                    else
                        sErr = (short)GetLastError();
                }
                else
#endif
                {
                    int iOK = DeviceIoControl(aHand1401[hand],(DWORD)U14_SENDSTRING,
                                    tstr, nChars,
                                    &rData,sizeof(PARAMBLK),&dwBytes,NULL);
                    if (iOK && (dwBytes >= sizeof(PARAMBLK)))
                        sErr = rData.sState;
                    else
                        sErr = U14ERR_DRIVCOMMS;
                }
