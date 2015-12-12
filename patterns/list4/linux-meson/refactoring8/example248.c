HCF_STATIC hcf_16* BASED xxxx[ ] = {
	&cfg_null.len,                          //CFG_NULL                      0x0820
#if defined MSF_COMPONENT_ID
	&cfg_drv_identity.len,                  //CFG_DRV_IDENTITY              0x0826
	&cfg_drv_sup_range.len,                 //CFG_DRV_SUP_RANGE             0x0827
	&cfg_drv_act_ranges_pri.len,            //CFG_DRV_ACT_RANGES_PRI        0x0828
	&cfg_drv_act_ranges_sta.len,            //CFG_DRV_ACT_RANGES_STA        0x0829
	&cfg_drv_act_ranges_hsi.len,            //CFG_DRV_ACT_RANGES_HSI        0x082A
	&cfg_drv_act_ranges_apf.len,            //CFG_DRV_ACT_RANGES_APF        0x082B
	&cfg_hcf_opt.len,                       //CFG_HCF_OPT                   0x082C
	NULL,                                   //IFB_PRIIdentity placeholder   0xFD02
	NULL,                                   //IFB_PRISup placeholder        0xFD03
#endif // MSF_COMPONENT_ID
	NULL                                    //endsentinel
};
