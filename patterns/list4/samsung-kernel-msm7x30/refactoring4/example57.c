#if (WNI_POLARIS_FW_PRODUCT == AP)
if (index >= CFG_AP_IBUF_MAX_SIZE)
#else
    if (index >= CFG_STA_IBUF_MAX_SIZE)
#endif
    {
        PELOGE(cfgLog(pMac, LOGE, FL("cfg index out of bounds %d\n"), index);)
        retVal = eSIR_CFG_INVALID_ID;
        return retVal;
    }
