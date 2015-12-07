#ifdef ZM_ENABLE_CENC
if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    encryMode = ZM_CENC;
                    zm_debug_msg0("Set CENC group Key");

                    /* Reset txiv and rxiv */
                    wd->ap.txiv[vapId][0] = 0x5c365c36;
                    wd->ap.txiv[vapId][1] = 0x5c365c36;
                    wd->ap.txiv[vapId][2] = 0x5c365c36;
                    wd->ap.txiv[vapId][3] = 0x5c365c36;

                    //zfCoreSetKey(dev, 0, 1, ZM_CENC, keyInfo.vapAddr,
                    //          (u32_t*) &keyInfo.key[16]);
                    key = (u32_t*) keyInfo.key;
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    encryMode = ZM_TKIP;
                    key = (u32_t *)keyInfo.key;

                    /* set MIC key to HMAC */
                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, broadcast,
                    //         (u32_t*) (&keyInfo.key[16]));
                    //zfCoreSetKey(dev, 0, 1, ZM_TKIP, keyInfo.vapAddr,
                    //           (u32_t*) (&keyInfo.key[16]));

                    zfMicSetKey(&(keyInfo.key[16]), &(wd->ap.bcMicKey[0]));
                    key = (u32_t*) keyInfo.key;
                }
