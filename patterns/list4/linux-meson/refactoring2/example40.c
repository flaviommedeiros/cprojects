#if !(DM_ODM_SUPPORT_TYPE & ODM_AP)
if ((pMptCtx->MptRfPath == ODM_RF_PATH_A) || (pDM_Odm->mp_mode == FALSE))
#endif
	{
		if (RegEB4 != 0)
		{
			_PHY_PathBFillIQKMatrix8723B(pAdapter, bPathBOK, result, final_candidate, (RegEC4 == 0));
		}
	}
