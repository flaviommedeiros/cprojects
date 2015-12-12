#if defined(ANI_OS_TYPE_LINUX) || defined(ANI_OS_TYPE_OSX)
if (sirReadU32N((tANI_U8*)pParam) == CFG_STA_MAGIC_DWORD)
#else
        if (*pParam == CFG_STA_MAGIC_DWORD)
#endif

        ap = 0;
