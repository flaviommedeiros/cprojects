if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT - 1 - vapId, 1, type, apMacAddr, micKey);
