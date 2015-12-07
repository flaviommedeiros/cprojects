if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
    {
        zfHpSetKey(dev, user, keyId + 1, type, (u16_t *)mac, micKey);
    }
