static u8 gp2a_original_image[8] =
{
#ifdef PROX_MODE_A
	0x00,  
	0x08,  
	0xC2,  
	0x04,
	0x01,
#else
	0x00,  
	0x08,  
	REGS_HYS_VAL_VO_0,
	0x04,
	0x03,
#endif //PROX_MODE_A	
};
