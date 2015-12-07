#ifdef INCLUDE_5701_AX_FIX
if ((pDevice->LoopBackMode == LM_EXT_LOOP_BACK_MODE) ||
                (pDevice->ChipRevId == T3_CHIP_ID_5701_A0 ||
                pDevice->ChipRevId == T3_CHIP_ID_5701_B0))
#else
            if (pDevice->LoopBackMode == LM_EXT_LOOP_BACK_MODE)
#endif
            {
                Value32 |= BCM540X_CONFIG_AS_MASTER |
                    BCM540X_ENABLE_CONFIG_AS_MASTER;
            }
