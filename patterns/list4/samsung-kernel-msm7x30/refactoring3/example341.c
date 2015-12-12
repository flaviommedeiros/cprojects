switch (event)
    {
#ifndef GEN6_ONWARDS
    case ePMC_SYSTEM_HIBERNATE:
        return pmcEnterLowPowerState(hHal);

    case ePMC_SYSTEM_RESUME:
        return pmcExitLowPowerState(hHal);

    case ePMC_HW_WLAN_SWITCH_OFF:
        pMac->pmc.hwWlanSwitchState = ePMC_SWITCH_OFF;
        return pmcEnterLowPowerState(hHal);

    case ePMC_HW_WLAN_SWITCH_ON:
        pMac->pmc.hwWlanSwitchState = ePMC_SWITCH_ON;
        return pmcExitLowPowerState(hHal);

    case ePMC_SW_WLAN_SWITCH_OFF:
        pMac->pmc.swWlanSwitchState = ePMC_SWITCH_OFF;
        return pmcEnterLowPowerState(hHal);

    case ePMC_SW_WLAN_SWITCH_ON:
        pMac->pmc.swWlanSwitchState = ePMC_SWITCH_ON;
        return pmcExitLowPowerState(hHal);

    case ePMC_BATTERY_OPERATION:
        pMac->pmc.powerSource = BATTERY_POWER;

        /* Turn on SMPS. */
        if (pMac->pmc.smpsEnabled)
        {
            if (pMac->pmc.smpsConfig.mode == ePMC_DYNAMIC_SMPS)
                htMimoPowerSaveState = eSIR_HT_MIMO_PS_DYNAMIC;
            if (pMac->pmc.smpsConfig.mode == ePMC_STATIC_SMPS)
                htMimoPowerSaveState = eSIR_HT_MIMO_PS_STATIC;
            if (pmcSendMessage(hHal, eWNI_PMC_SMPS_STATE_IND, &htMimoPowerSaveState,
                               sizeof(tSirMacHTMIMOPowerSaveState)) != eHAL_STATUS_SUCCESS)   
                return eHAL_STATUS_FAILURE;
        }
        return eHAL_STATUS_SUCCESS;

    case ePMC_AC_OPERATION:
        pMac->pmc.powerSource = AC_POWER;

        /* Turn off SMPS. */
        if (!pMac->pmc.smpsConfig.enterOnAc)
        {
            htMimoPowerSaveState = eSIR_HT_MIMO_PS_NO_LIMIT;
            if (pmcSendMessage(hHal, eWNI_PMC_SMPS_STATE_IND, &htMimoPowerSaveState,
                               sizeof(tSirMacHTMIMOPowerSaveState)) != eHAL_STATUS_SUCCESS)
                return eHAL_STATUS_FAILURE;
        }
        return eHAL_STATUS_SUCCESS;
#endif //GEN6_ONWARDS
    default:
        smsLog(pMac, LOGE, FL("Invalid event %d\n"), event);
        PMC_ABORT;
        return eHAL_STATUS_FAILURE;
    }
