#ifndef _WIN64
if (!USE_NT_DIOC(sHand)) 
    {   /* Windows 9x DIOC methods? */
        if (DeviceIoControl(aHand1401[sHand], lCode, NULL, 0, pBlk,sizeof(TCSBLOCK),&dwBytes,NULL))
            return (short)((dwBytes>=sizeof(TCSBLOCK)) ? U14ERR_NOERROR : U14ERR_DRIVCOMMS);
        else
            return (short)GetLastError();
    }
    else
#endif
    {                                       /* Windows NT or USB driver */
        PARAMBLK rWork;
        rWork.sState = U14ERR_DRIVCOMMS;
        if (DeviceIoControl(aHand1401[sHand], lCode, NULL, 0, &rWork,sizeof(PARAMBLK),&dwBytes,NULL) &&
            (dwBytes >= sizeof(PARAMBLK)))
        {
            *pBlk = rWork.csBlock;
            return rWork.sState;
        }
    }
