#ifdef ZM_ENABLE_CENC
if (keyInfo.flag & ZM_KEY_FLAG_CENC)
            {
                u16_t boardcastAddr[3] = {0xffff, 0xffff, 0xffff};
                u16_t Addr_a[] = { 0x0000, 0x0080, 0x0901};
                u16_t Addr_b[] = { 0x0000, 0x0080, 0x0902};
                /* CENC test: user0,1 and user2 for boardcast */
                wd->sta.encryMode = ZM_CENC;
                zfCoreSetKey(dev, 0, 1, ZM_CENC, (u16_t *)Addr_a, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 0, 0, ZM_CENC, (u16_t *)Addr_a, (u32_t*) keyInfo.key);

                zfCoreSetKey(dev, 1, 1, ZM_CENC, (u16_t *)Addr_b, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 1, 0, ZM_CENC, (u16_t *)Addr_b, (u32_t*) keyInfo.key);

                zfCoreSetKey(dev, 2, 1, ZM_CENC, (u16_t *)boardcastAddr, (u32_t*) (&keyInfo.key[16]));
                zfCoreSetKey(dev, 2, 0, ZM_CENC, (u16_t *)boardcastAddr, (u32_t*) keyInfo.key);

                /* Initialize PN sequence */
                wd->sta.txiv[0] = 0x5c365c36;
                wd->sta.txiv[1] = 0x5c365c36;
                wd->sta.txiv[2] = 0x5c365c36;
                wd->sta.txiv[3] = 0x5c365c36;
            }
            else
#endif //ZM_ENABLE_CENC
            {
                wd->sta.encryMode = ZM_TKIP;
                zfCoreSetKey(dev, 64, 1, ZM_TKIP, (u16_t *)keyInfo.macAddr, (u32_t*) micKey);
                zfCoreSetKey(dev, 64, 0, ZM_TKIP, (u16_t *)keyInfo.macAddr, (u32_t*) keyInfo.key);
            }
