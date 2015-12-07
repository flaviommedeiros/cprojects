#ifdef ZM_ENABLE_CENC
if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    zm_debug_msg0("Set CENC pairwise Key");

                    wd->sta.encryMode = ZM_CENC;

                    /* Reset txiv and rxiv */
                    wd->sta.txiv[0] = 0x5c365c36;
                    wd->sta.txiv[1] = 0x5c365c36;
                    wd->sta.txiv[2] = 0x5c365c36;
                    wd->sta.txiv[3] = 0x5c365c36;

                    wd->sta.rxiv[0] = 0x5c365c37;
                    wd->sta.rxiv[1] = 0x5c365c36;
                    wd->sta.rxiv[2] = 0x5c365c36;
                    wd->sta.rxiv[3] = 0x5c365c36;

                    /* Set Key Index */
                    wd->sta.cencKeyId = keyInfo.keyIndex;

                    //zfCoreSetKey(dev, id+1, 1, ZM_CENC, (u16_t *)keyInfo.macAddr,
                    //         (u32_t*) &keyInfo.key[16]);
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    wd->sta.encryMode = ZM_TKIP;

                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, wd->sta.bssid,
                    //         (u32_t*) &keyInfo.key[16]);

                    zfMicSetKey(&keyInfo.key[16], &wd->sta.txMicKey);
                    zfMicSetKey(&keyInfo.key[24],
                                &wd->sta.rxMicKey[keyInfo.keyIndex]);
                }
