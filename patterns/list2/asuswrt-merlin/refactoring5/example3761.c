#ifdef ZM_ENABLE_CENC
if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    zm_debug_msg0("Set CENC pairwise Key");

                    wd->ap.staTable[id].encryMode = ZM_CENC;

                    /* Reset txiv and rxiv */
                    wd->ap.staTable[id].txiv[0] = 0x5c365c37;
                    wd->ap.staTable[id].txiv[1] = 0x5c365c36;
                    wd->ap.staTable[id].txiv[2] = 0x5c365c36;
                    wd->ap.staTable[id].txiv[3] = 0x5c365c36;

                    wd->ap.staTable[id].rxiv[0] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[1] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[2] = 0x5c365c36;
                    wd->ap.staTable[id].rxiv[3] = 0x5c365c36;

                    /* Set Key Index */
                    wd->ap.staTable[id].cencKeyIdx = keyInfo.keyIndex;

                    //zfCoreSetKey(dev, id+1, 1, ZM_CENC, (u16_t *)keyInfo.macAddr,
                    //          (u32_t*) &keyInfo.key[16]);
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    wd->ap.staTable[id].encryMode = ZM_TKIP;

                    zfMemoryCopy(micKey, &keyInfo.key[16], 8);
                    zfMemoryCopy(&micKey[8], &keyInfo.key[24], 8);

                    //zfCoreSetKey(dev, id+1, 1, ZM_TKIP, (u16_t *)keyInfo.macAddr,
                    //           (u32_t*) micKey);

                    /* For fragmentation, we use software MIC */
                    zfMemoryCopy((u8_t *)&(wd->ap.staTable[id].txMicKey), &(keyInfo.key[16]), 8);
                    zfMemoryCopy((u8_t *)&(wd->ap.staTable[id].rxMicKey), &(keyInfo.key[24]), 8);

                }
