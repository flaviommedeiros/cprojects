#ifdef MHAWB_SUPPORT
if (SiiDrvHawbEnable(false))
#endif
    {
        // Found a pending message, send it out
        if ( SiiDrvInternalCBusWriteCommand( &pCbus->chState.request[ CH_ACTIVE_INDEX] ))
        {
            pCbus->chState.state = CBUS_SENT;
            pCbus->chState.request[ CH_ACTIVE_INDEX].reqStatus = CBUS_REQ_SENT;
        }
        else
        {
            result = ERROR_WRITE_FAILED;
        }
    }
