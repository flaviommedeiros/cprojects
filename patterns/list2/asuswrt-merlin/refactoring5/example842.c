#ifdef BCM_WOL
if (pDevice->RestoreOnWakeUp)
    {
        LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, 0);
        pDevice->advertising1000 = 0;
        Value32 = PHY_AN_AD_10BASET_FULL | PHY_AN_AD_10BASET_HALF;
        if (pDevice->WolSpeed == WOL_SPEED_100MB)
        {
            Value32 |= PHY_AN_AD_100BASETX_FULL | PHY_AN_AD_100BASETX_HALF;
        }
        Value32 |= PHY_AN_AD_PROTOCOL_802_3_CSMA_CD;
        Value32 |= GetPhyAdFlowCntrlSettings(pDevice);
        LM_WritePhy(pDevice, PHY_AN_AD_REG, Value32);
        pDevice->advertising = Value32;
    }
    /* Setup the auto-negotiation advertisement register. */
    else if(LineSpeed == LM_LINE_SPEED_UNKNOWN)
#else
    /* Setup the auto-negotiation advertisement register. */
    if(LineSpeed == LM_LINE_SPEED_UNKNOWN)
#endif
    {
        /* Setup the 10/100 Mbps auto-negotiation advertisement register. */
        Value32 = PHY_AN_AD_PROTOCOL_802_3_CSMA_CD | PHY_AN_AD_ALL_SPEEDS;
        Value32 |= GetPhyAdFlowCntrlSettings(pDevice);

        LM_WritePhy(pDevice, PHY_AN_AD_REG, Value32);
        pDevice->advertising = Value32;

        /* Advertise 1000Mbps */
        if (!(pDevice->PhyFlags & PHY_NO_GIGABIT))
        {
            Value32 = BCM540X_AN_AD_ALL_1G_SPEEDS;

#ifdef INCLUDE_5701_AX_FIX
            /* slave mode.  This will force the PHY to operate in */
            /* master mode. */
            if(pDevice->ChipRevId == T3_CHIP_ID_5701_A0 ||
                pDevice->ChipRevId == T3_CHIP_ID_5701_B0)
            {
                Value32 |= BCM540X_CONFIG_AS_MASTER |
                    BCM540X_ENABLE_CONFIG_AS_MASTER;
            }
#endif

            LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, Value32);
            pDevice->advertising1000 = Value32;
        }
	else
	{
            LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, 0);
            pDevice->advertising1000 = 0;
	}
    }
    else
    {
        if ((pDevice->PhyFlags & PHY_NO_GIGABIT) &&
            (LineSpeed == LM_LINE_SPEED_1000MBPS))
        {
            LineSpeed = LM_LINE_SPEED_100MBPS;
        }
        if(LineSpeed == LM_LINE_SPEED_1000MBPS)
        {
            Value32 = PHY_AN_AD_PROTOCOL_802_3_CSMA_CD;
            Value32 |= GetPhyAdFlowCntrlSettings(pDevice);

            LM_WritePhy(pDevice, PHY_AN_AD_REG, Value32);
            pDevice->advertising = Value32;

            if(DuplexMode != LM_DUPLEX_MODE_FULL)
            {
                Value32 = BCM540X_AN_AD_1000BASET_HALF;
            }
            else
            {
                Value32 = BCM540X_AN_AD_1000BASET_FULL;
            }

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
            LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, Value32);
            pDevice->advertising1000 = Value32;
            if (pDevice->LoopBackMode == LM_EXT_LOOP_BACK_MODE)
            {
                if ((pDevice->PhyId & PHY_ID_MASK) == PHY_BCM5401_PHY_ID)
                {
                    LM_WritePhy(pDevice, BCM5401_AUX_CTRL, 0x8c20);
                }
                else
                {
                    LM_WritePhy(pDevice, BCM5401_AUX_CTRL, 0x0007);
                    LM_ReadPhy(pDevice, BCM5401_AUX_CTRL, &PhyReg18);
                    PhyReg18 |= 0x8000;    /* set loop back */
                    LM_WritePhy(pDevice, BCM5401_AUX_CTRL, PhyReg18);
                }
            }
        }
        else if(LineSpeed == LM_LINE_SPEED_100MBPS)
        {
            LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, 0);
            pDevice->advertising1000 = 0;

            if(DuplexMode != LM_DUPLEX_MODE_FULL)
            {
                Value32 = PHY_AN_AD_100BASETX_HALF;
            }
            else
            {
                Value32 = PHY_AN_AD_100BASETX_FULL;
            }

            Value32 |= PHY_AN_AD_PROTOCOL_802_3_CSMA_CD;
            Value32 |= GetPhyAdFlowCntrlSettings(pDevice);

            LM_WritePhy(pDevice, PHY_AN_AD_REG, Value32);
            pDevice->advertising = Value32;
        }
        else if(LineSpeed == LM_LINE_SPEED_10MBPS)
        {
            LM_WritePhy(pDevice, BCM540X_1000BASET_CTRL_REG, 0);
            pDevice->advertising1000 = 0;

            if(DuplexMode != LM_DUPLEX_MODE_FULL)
            {
                Value32 = PHY_AN_AD_10BASET_HALF;
            }
            else
            {
                Value32 = PHY_AN_AD_10BASET_FULL;
            }

            Value32 |= PHY_AN_AD_PROTOCOL_802_3_CSMA_CD;
            Value32 |= GetPhyAdFlowCntrlSettings(pDevice);

            LM_WritePhy(pDevice, PHY_AN_AD_REG, Value32);
            pDevice->advertising = Value32;
        }
    }
