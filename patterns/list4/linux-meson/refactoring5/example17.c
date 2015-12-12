#ifdef NEW_DNLP_IN_SHARPNESS
if(dnlp_sel == NEW_DNLP_IN_SHARPNESS){
	WRITE_VPP_REG(DNLP_00, ve_dnlp_reg[0]);
	WRITE_VPP_REG(DNLP_01, ve_dnlp_reg[1]);
	WRITE_VPP_REG(DNLP_02, ve_dnlp_reg[2]);
	WRITE_VPP_REG(DNLP_03, ve_dnlp_reg[3]);
	WRITE_VPP_REG(DNLP_04, ve_dnlp_reg[4]);
	WRITE_VPP_REG(DNLP_05, ve_dnlp_reg[5]);
	WRITE_VPP_REG(DNLP_06, ve_dnlp_reg[6]);
	WRITE_VPP_REG(DNLP_07, ve_dnlp_reg[7]);
	WRITE_VPP_REG(DNLP_08, ve_dnlp_reg[8]);
	WRITE_VPP_REG(DNLP_09, ve_dnlp_reg[9]);
	WRITE_VPP_REG(DNLP_10, ve_dnlp_reg[10]);
	WRITE_VPP_REG(DNLP_11, ve_dnlp_reg[11]);
	WRITE_VPP_REG(DNLP_12, ve_dnlp_reg[12]);
	WRITE_VPP_REG(DNLP_13, ve_dnlp_reg[13]);
	WRITE_VPP_REG(DNLP_14, ve_dnlp_reg[14]);
	WRITE_VPP_REG(DNLP_15, ve_dnlp_reg[15]);
	}else
#endif
	{
	WRITE_VPP_REG(VPP_DNLP_CTRL_00, ve_dnlp_reg[0]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_01, ve_dnlp_reg[1]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_02, ve_dnlp_reg[2]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_03, ve_dnlp_reg[3]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_04, ve_dnlp_reg[4]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_05, ve_dnlp_reg[5]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_06, ve_dnlp_reg[6]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_07, ve_dnlp_reg[7]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_08, ve_dnlp_reg[8]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_09, ve_dnlp_reg[9]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_10, ve_dnlp_reg[10]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_11, ve_dnlp_reg[11]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_12, ve_dnlp_reg[12]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_13, ve_dnlp_reg[13]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_14, ve_dnlp_reg[14]);
	WRITE_VPP_REG(VPP_DNLP_CTRL_15, ve_dnlp_reg[15]);
	}
