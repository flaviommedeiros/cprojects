#if MP_DRIVER == 1
if ((pMptCtx->MptRfPath == ODM_RF_PATH_A) || (pDM_Odm->mp_mode == FALSE))
#endif
	{
		if (RegE94 != 0)
		{
#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
			_PHY_PathAFillIQKMatrix8723B(pAdapter, bPathAOK, result, final_candidate, (RegEA4 == 0));
#else
			_PHY_PathAFillIQKMatrix8723B(pDM_Odm, bPathAOK, result, final_candidate, (RegEA4 == 0));
#endif
		}
	}
