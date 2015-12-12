#if (RTL8195A_SUPPORT == 0)
if (pDM_Odm->SupportICType & ODM_IC_11AC_SERIES)
		value32 = ODM_GetBBReg(pDM_Odm, ODM_REG_NHM_CNT_11AC, bMaskDWord);
	else if (pDM_Odm->SupportICType & ODM_IC_11N_SERIES)
#endif
		value32 = ODM_GetBBReg(pDM_Odm, ODM_REG_NHM_CNT_11N, bMaskDWord);
