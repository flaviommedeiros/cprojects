if ((type == ZM_TKIP)

#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
    {
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT+keyId, 1, type, macAddr, micKey);
    }
