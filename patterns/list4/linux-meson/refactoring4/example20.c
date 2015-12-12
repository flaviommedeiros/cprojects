#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
if (ThermalValue > pHalData->EEPROMThermalMeter)
#else
		if (ThermalValue > pDM_Odm->priv->pmib->dot11RFEntry.ther)
#endif
		{
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("Temperature(%d) higher than PG value(%d)\n", ThermalValue, pHalData->EEPROMThermalMeter));			

			if (pDM_Odm->SupportICType == ODM_RTL8188E || pDM_Odm->SupportICType == ODM_RTL8192E || pDM_Odm->SupportICType == ODM_RTL8821 ||
				pDM_Odm->SupportICType == ODM_RTL8812 || pDM_Odm->SupportICType == ODM_RTL8723B || pDM_Odm->SupportICType == ODM_RTL8814A || 
				pDM_Odm->SupportICType == ODM_RTL8822B) {
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("**********Enter POWER Tracking MIX_MODE**********\n"));
				for (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
						(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, MIX_MODE, p, 0);
			}
			else 
			{
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("**********Enter POWER Tracking BBSWING_MODE**********\n"));
				for (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
						(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, BBSWING, p, Indexforchannel);
			}
		}
		else
		{
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("Temperature(%d) lower than PG value(%d)\n", ThermalValue, pHalData->EEPROMThermalMeter));

			if (pDM_Odm->SupportICType == ODM_RTL8188E || pDM_Odm->SupportICType == ODM_RTL8192E || pDM_Odm->SupportICType == ODM_RTL8821 ||
				pDM_Odm->SupportICType == ODM_RTL8812 || pDM_Odm->SupportICType == ODM_RTL8723B || pDM_Odm->SupportICType == ODM_RTL8814A ||
				pDM_Odm->SupportICType == ODM_RTL8822B) {

				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("**********Enter POWER Tracking MIX_MODE**********\n"));
				for (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
					(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, MIX_MODE, p, Indexforchannel);
			}
			else
			{
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("**********Enter POWER Tracking BBSWING_MODE**********\n"));
				for (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
					(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, BBSWING, p, Indexforchannel);
			}
			
		}
