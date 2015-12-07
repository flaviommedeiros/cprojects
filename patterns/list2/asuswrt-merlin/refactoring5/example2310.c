#ifdef ZM_ENABLE_CENC
if (keyInfo.flag & ZM_KEY_FLAG_CENC)
                {
                    encryMode = ZM_CENC;
                    zm_debug_msg0("Set CENC group Key");

                    /* Reset txiv and rxiv */
                    wd->sta.rxivGK[0] = 0x5c365c36;
                    wd->sta.rxivGK[1] = 0x5c365c36;
                    wd->sta.rxivGK[2] = 0x5c365c36;
                    wd->sta.rxivGK[3] = 0x5c365c36;

                    //zfCoreSetKey(dev, 0, 1, ZM_CENC, keyInfo.vapAddr,
                    //         (u32_t*) &keyInfo.key[16]);
                    key = (u32_t*) keyInfo.key;
                }
                else
#endif //ZM_ENABLE_CENC
                {
                    encryMode = ZM_TKIP;
                    key = (u32_t*) wd->sta.rxSeed[keyInfo.keyIndex].tk;

                    if ( !(keyInfo.flag & ZM_KEY_FLAG_INIT_IV) )
                    {
                        wd->sta.rxSeed[keyInfo.keyIndex].iv16 = 0;
                        wd->sta.rxSeed[keyInfo.keyIndex].iv32 = 0;
                    }

                    /* set MIC key to HMAC */
                    //zfCoreSetKey(dev, 8, 1, ZM_TKIP, broadcast,
                    //         (u32_t*) (&keyInfo.key[16]));

                    zfMicSetKey(&keyInfo.key[24],
                                &wd->sta.rxMicKey[keyInfo.keyIndex]);
                }
