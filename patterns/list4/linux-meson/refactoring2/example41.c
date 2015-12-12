#if (MP_DRIVER == 1)
if (pDM_Odm->mp_mode == TRUE)
#endif
		// <Kordan> RFCalibrateInfo.RegA24 will be initialized when ODM HW configuring, but MP configures with para files.
		pDM_Odm->RFCalibrateInfo.RegA24 = 0x090e1317;
