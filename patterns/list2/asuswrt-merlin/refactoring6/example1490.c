if ( !mmd_check_comp( (void*)&cfg_drv_act_ranges_hsi, &ifbp->IFB_HSISup)				 /* 22*/
#if ( (HCF_TYPE) & HCF_TYPE_PRELOADED ) == 0
//;? the PRI compatibility check is only relevant for DHF
			 || !mmd_check_comp( (void*)&cfg_drv_act_ranges_pri, &ifbp->IFB_PRISup)
#endif // HCF_TYPE_PRELOADED
		   ) {
			ifbp->IFB_CardStat = CARD_STAT_INCOMP_PRI;
			rc = HCF_ERR_INCOMP_PRI;
		}
