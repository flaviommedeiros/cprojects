switch (cmd)
    {
    case ZM_HAL_ANI_NOISE_IMMUNITY_LEVEL:
    {
        u32_t level = param;

        if (level >= N(HpPriv->totalSizeDesired))
        {
          zm_debug_msg1("level out of range, desired level : ", level);
          zm_debug_msg1("max level : ", N(HpPriv->totalSizeDesired));
          return FALSE;
        }

        zfDelayWriteInternalReg(dev, AR_PHY_DESIRED_SZ,
                (HpPriv->regPHYDesiredSZ & ~AR_PHY_DESIRED_SZ_TOT_DES)
                | ((HpPriv->totalSizeDesired[level] << AR_PHY_DESIRED_SZ_TOT_DES_S)
                & AR_PHY_DESIRED_SZ_TOT_DES));
        zfDelayWriteInternalReg(dev, AR_PHY_AGC_CTL1,
                (HpPriv->regPHYAgcCtl1 & ~AR_PHY_AGC_CTL1_COARSE_LOW)
                | ((HpPriv->coarseLow[level] << AR_PHY_AGC_CTL1_COARSE_LOW_S)
                & AR_PHY_AGC_CTL1_COARSE_LOW));
        zfDelayWriteInternalReg(dev, AR_PHY_AGC_CTL1,
                (HpPriv->regPHYAgcCtl1 & ~AR_PHY_AGC_CTL1_COARSE_HIGH)
                | ((HpPriv->coarseHigh[level] << AR_PHY_AGC_CTL1_COARSE_HIGH_S)
                & AR_PHY_AGC_CTL1_COARSE_HIGH));
        zfDelayWriteInternalReg(dev, AR_PHY_FIND_SIG,
                (HpPriv->regPHYFindSig & ~AR_PHY_FIND_SIG_FIRPWR)
                | ((HpPriv->firpwr[level] << AR_PHY_FIND_SIG_FIRPWR_S)
                & AR_PHY_FIND_SIG_FIRPWR));
        zfFlushDelayWrite(dev);

        if (level > aniState->noiseImmunityLevel)
            HpPriv->stats.ast_ani_niup++;
        else if (level < aniState->noiseImmunityLevel)
            HpPriv->stats.ast_ani_nidown++;
        aniState->noiseImmunityLevel = (u8_t)level;
        break;
    }
    case ZM_HAL_ANI_OFDM_WEAK_SIGNAL_DETECTION:
    {
        const TABLE m1ThreshLow   = { 127,   50 };
        const TABLE m2ThreshLow   = { 127,   40 };
        const TABLE m1Thresh      = { 127, 0x4d };
        const TABLE m2Thresh      = { 127, 0x40 };
        const TABLE m2CountThr    = {  31,   16 };
        const TABLE m2CountThrLow = {  63,   48 };
        u32_t on = param ? 1 : 0;

        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR_LOW,
                (HpPriv->regPHYSfcorrLow & ~AR_PHY_SFCORR_LOW_M1_THRESH_LOW)
                | ((m1ThreshLow[on] << AR_PHY_SFCORR_LOW_M1_THRESH_LOW_S)
                & AR_PHY_SFCORR_LOW_M1_THRESH_LOW));
        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR_LOW,
                (HpPriv->regPHYSfcorrLow & ~AR_PHY_SFCORR_LOW_M2_THRESH_LOW)
                | ((m2ThreshLow[on] << AR_PHY_SFCORR_LOW_M2_THRESH_LOW_S)
                & AR_PHY_SFCORR_LOW_M2_THRESH_LOW));
        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR,
                (HpPriv->regPHYSfcorr & ~AR_PHY_SFCORR_M1_THRESH)
                | ((m1Thresh[on] << AR_PHY_SFCORR_M1_THRESH_S)
                & AR_PHY_SFCORR_M1_THRESH));
        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR,
                (HpPriv->regPHYSfcorr & ~AR_PHY_SFCORR_M2_THRESH)
                | ((m2Thresh[on] << AR_PHY_SFCORR_M2_THRESH_S)
                & AR_PHY_SFCORR_M2_THRESH));
        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR,
                (HpPriv->regPHYSfcorr & ~AR_PHY_SFCORR_M2COUNT_THR)
                | ((m2CountThr[on] << AR_PHY_SFCORR_M2COUNT_THR_S)
                & AR_PHY_SFCORR_M2COUNT_THR));
        zfDelayWriteInternalReg(dev, AR_PHY_SFCORR_LOW,
                (HpPriv->regPHYSfcorrLow & ~AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW)
                | ((m2CountThrLow[on] << AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW_S)
                & AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW));

        if (on)
        {
            zfDelayWriteInternalReg(dev, AR_PHY_SFCORR_LOW,
                    HpPriv->regPHYSfcorrLow | AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);
        }
        else
        {
            zfDelayWriteInternalReg(dev, AR_PHY_SFCORR_LOW,
                    HpPriv->regPHYSfcorrLow & ~AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);
        }
        zfFlushDelayWrite(dev);
        if (!on != aniState->ofdmWeakSigDetectOff)
        {
            if (on)
                HpPriv->stats.ast_ani_ofdmon++;
            else
                HpPriv->stats.ast_ani_ofdmoff++;
            aniState->ofdmWeakSigDetectOff = !on;
        }
        break;
    }
    case ZM_HAL_ANI_CCK_WEAK_SIGNAL_THR:
    {
        const TABLE weakSigThrCck = { 8, 6 };
        u32_t high = param ? 1 : 0;

        zfDelayWriteInternalReg(dev, AR_PHY_CCK_DETECT,
                (HpPriv->regPHYCckDetect & ~AR_PHY_CCK_DETECT_WEAK_SIG_THR_CCK)
                | ((weakSigThrCck[high] << AR_PHY_CCK_DETECT_WEAK_SIG_THR_CCK_S)
                & AR_PHY_CCK_DETECT_WEAK_SIG_THR_CCK));
        zfFlushDelayWrite(dev);
        if (high != aniState->cckWeakSigThreshold)
        {
            if (high)
                HpPriv->stats.ast_ani_cckhigh++;
            else
                HpPriv->stats.ast_ani_ccklow++;
            aniState->cckWeakSigThreshold = (u8_t)high;
        }
        break;
    }
    case ZM_HAL_ANI_FIRSTEP_LEVEL:
    {
        const TABLE firstep = { 0, 4, 8 };
        u32_t level = param;

        if (level >= N(firstep))
        {
            zm_debug_msg1("level out of range, desired level : ", level);
            zm_debug_msg1("max level : ", N(firstep));
            return FALSE;
        }
        zfDelayWriteInternalReg(dev, AR_PHY_FIND_SIG,
                (HpPriv->regPHYFindSig & ~AR_PHY_FIND_SIG_FIRSTEP)
                | ((firstep[level] << AR_PHY_FIND_SIG_FIRSTEP_S)
                & AR_PHY_FIND_SIG_FIRSTEP));
        zfFlushDelayWrite(dev);
        if (level > aniState->firstepLevel)
            HpPriv->stats.ast_ani_stepup++;
        else if (level < aniState->firstepLevel)
            HpPriv->stats.ast_ani_stepdown++;
        aniState->firstepLevel = (u8_t)level;
        break;
    }
    case ZM_HAL_ANI_SPUR_IMMUNITY_LEVEL:
    {
        const TABLE cycpwrThr1 = { 2, 4, 6, 8, 10, 12, 14, 16 };
        u32_t level = param;

        if (level >= N(cycpwrThr1))
        {
            zm_debug_msg1("level out of range, desired level : ", level);
            zm_debug_msg1("max level : ", N(cycpwrThr1));
            return FALSE;
        }
        zfDelayWriteInternalReg(dev, AR_PHY_TIMING5,
                (HpPriv->regPHYTiming5 & ~AR_PHY_TIMING5_CYCPWR_THR1)
                | ((cycpwrThr1[level] << AR_PHY_TIMING5_CYCPWR_THR1_S)
                & AR_PHY_TIMING5_CYCPWR_THR1));
        zfFlushDelayWrite(dev);
        if (level > aniState->spurImmunityLevel)
            HpPriv->stats.ast_ani_spurup++;
        else if (level < aniState->spurImmunityLevel)
            HpPriv->stats.ast_ani_spurdown++;
        aniState->spurImmunityLevel = (u8_t)level;
        break;
    }
    case ZM_HAL_ANI_PRESENT:
        break;
#ifdef AH_PRIVATE_DIAG
    case ZM_HAL_ANI_MODE:
        if (param == 0)
        {
            HpPriv->procPhyErr &= ~ZM_HAL_PROCESS_ANI;
            /* Turn off HW counters if we have them */
            zfHpAniDetach(dev);
            //zfHpSetRxFilter(dev, zfHpGetRxFilter(dev) &~ HAL_RX_FILTER_PHYERR);
        }
        else
        {           /* normal/auto mode */
            HpPriv->procPhyErr |= ZM_HAL_PROCESS_ANI;
            if (HpPriv->hasHwPhyCounters)
            {
                //zfHpSetRxFilter(dev, zfHpGetRxFilter(dev) &~ HAL_RX_FILTER_PHYERR);
            }
            else
            {
                //zfHpSetRxFilter(dev, zfHpGetRxFilter(dev) | HAL_RX_FILTER_PHYERR);
            }
        }
        break;
    case ZM_HAL_ANI_PHYERR_RESET:
        HpPriv->stats.ast_ani_ofdmerrs = 0;
        HpPriv->stats.ast_ani_cckerrs = 0;
        break;
#endif /* AH_PRIVATE_DIAG */
    default:
        zm_debug_msg1("invalid cmd ", cmd);
        return FALSE;
    }
