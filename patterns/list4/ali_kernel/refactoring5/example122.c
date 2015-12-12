#ifdef DOT11_N_SUPPORT
if (pAdapter->CommonCfg.PhyMode == PHY_11AN_MIXED)
                    pAdapter->CommonCfg.CentralChannel = 36;
                else
#endif // DOT11_N_SUPPORT //
                    pAdapter->CommonCfg.CentralChannel = 6;
