#ifdef NEW_DNLP_IN_SHARPNESS
if(dnlp_sel == NEW_DNLP_IN_SHARPNESS){
	WRITE_VPP_REG_BITS(DNLP_EN, 0, 0, 1);
	}else
#endif
	{
	WRITE_VPP_REG_BITS(VPP_VE_ENABLE_CTRL, 0, DNLP_EN_BIT, DNLP_EN_WID);
	}