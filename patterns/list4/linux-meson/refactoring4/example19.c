#if (DM_ODM_SUPPORT_TYPE & (ODM_CE|ODM_AP))
if(bReCovery)
#else//for ODM_WIN
	if(bReCovery && (!pAdapter->bInHctTest))  //YJ,add for PowerTest,120405
#endif	
	{
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD, ("PHY_IQCalibrate_8723B: Return due to bReCovery!\n"));
#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
		_PHY_ReloadADDARegisters8723B(pAdapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
#else
		_PHY_ReloadADDARegisters8723B(pDM_Odm, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
#endif
		goto out;
	}
