#ifndef _WIN64
if (!USE_NT_DIOC(hand))                         /* Use Win 9x DIOC? */
    {
        DWORD dwBytes;
        VXTRANSFERDESC vxDesc;                      /* Structure to pass to VXD */
        vxDesc.wArea = wArea;                       /* Copy across simple params */
        vxDesc.dwLength = dwLength;

        // Check we are not asking an old driver for more than area 0
        if ((wArea != 0) && (U14DriverVersion(hand) < 0x00010002L))
            sErr = U14ERR_DRIVTOOOLD;
        else
        {
            vxDesc.dwAddrOfs = (DWORD)pvBuff;       /* 32 bit offset */
            vxDesc.wAddrSel  = 0;

            if (DeviceIoControl(aHand1401[hand], (DWORD)U14_SETTRANSFER,
                                pvBuff,dwLength,    /* Will translate pointer */
                                &vxDesc,sizeof(VXTRANSFERDESC),
                                &dwBytes,NULL))
            {
                if (dwBytes >= sizeof(VXTRANSFERDESC)) /* Driver OK ? */
                    sErr = U14ERR_NOERROR;
                else
                    sErr = U14ERR_DRIVCOMMS;        /* Else never got there */
            }
            else
                sErr = (short)GetLastError();
        }
    }
    else
#endif
    {
        PARAMBLK rWork;
        DWORD dwBytes;
        td.wArea = wArea;     /* Pure NT - put data into struct */
        td.lpvBuff = pvBuff;
        td.dwLength = dwLength;
        td.eSize = 0;                // Dummy element size

        if (DeviceIoControl(aHand1401[hand],(DWORD)U14_SETTRANSFER,
                            &td,sizeof(TRANSFERDESC),
                            &rWork,sizeof(PARAMBLK),&dwBytes,NULL))
        {
            if (dwBytes >= sizeof(PARAMBLK))    // maybe error from driver?
                sErr = rWork.sState;            // will report any error
            else
                sErr = U14ERR_DRIVCOMMS;        // Else never got there
        }
        else
            sErr = U14ERR_DRIVCOMMS;
    }
