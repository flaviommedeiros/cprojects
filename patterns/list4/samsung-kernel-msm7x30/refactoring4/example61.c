#if defined(ANI_PRODUCT_TYPE_AP)
if (sirReadU32N((tANI_U8*)pParam) == CFG_AP_MAGIC_DWORD)
#else
    if (*pParam == CFG_AP_MAGIC_DWORD)
#endif
        ap = 1;
    else


#if defined(ANI_OS_TYPE_LINUX) || defined(ANI_OS_TYPE_OSX)
        if (sirReadU32N((tANI_U8*)pParam) == CFG_STA_MAGIC_DWORD)
#else
        if (*pParam == CFG_STA_MAGIC_DWORD)
#endif

        ap = 0;
