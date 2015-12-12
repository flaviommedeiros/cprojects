#ifdef ANI_PRODUCT_TYPE_AP
if (ap)
    {
        pMac->cfg.gCfgMaxIBufSize = CFG_AP_IBUF_MAX_SIZE;
        pMac->cfg.gCfgMaxSBufSize = CFG_AP_SBUF_MAX_SIZE;
    }
    else
#endif /* (WNI_POLARIS_FW_PRODUCT == AP) */
    {
        pMac->cfg.gCfgMaxIBufSize = CFG_STA_IBUF_MAX_SIZE;
        pMac->cfg.gCfgMaxSBufSize = CFG_STA_SBUF_MAX_SIZE;
    }
