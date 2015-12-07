if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
            zfHpSetKey(dev, (staAid-1), 1, type, staMacAddr, micKey);
