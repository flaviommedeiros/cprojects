#if (WNI_POLARIS_FW_PRODUCT == AP)
if (index >= CFG_AP_SBUF_MAX_SIZE-1)
#else
    if (index >= CFG_STA_SBUF_MAX_SIZE-1)
#endif
    {
        PELOGE(cfgLog(pMac, LOGE, FL("cfg index out of bounds %d\n"), index);)
        retVal = eSIR_CFG_INVALID_ID;
        return retVal;
    }
