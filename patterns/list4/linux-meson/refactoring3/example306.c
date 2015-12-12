switch(psta->wireless_mode)
	{
		case WIRELESS_11B:
			raid = RATEID_IDX_B;
			break;
		case WIRELESS_11A:
		case WIRELESS_11G:
			raid = RATEID_IDX_G;
			break;
		case WIRELESS_11BG:
			raid = RATEID_IDX_BG;
			break;
		case WIRELESS_11_24N:
		case WIRELESS_11_5N:
		case WIRELESS_11A_5N:
		case WIRELESS_11G_24N:
			if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
				raid = RATEID_IDX_GN_N1SS;
			else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
				raid = RATEID_IDX_GN_N2SS;
			else if (rf_type == RF_3T3R)
				raid = RATEID_IDX_BGN_3SS;
			else
				DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			break;
		case WIRELESS_11B_24N:
		case WIRELESS_11BG_24N:
			if (psta->bw_mode == CHANNEL_WIDTH_20) {
				if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
					raid = RATEID_IDX_BGN_20M_1SS_BN;
				else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
					raid = RATEID_IDX_BGN_20M_2SS_BN;
				else if(rf_type == RF_3T3R)
					raid = RATEID_IDX_BGN_3SS;
				else
				DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			} else {
				if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
					raid = RATEID_IDX_BGN_40M_1SS;
				else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
					raid = RATEID_IDX_BGN_40M_2SS;
				else if(rf_type == RF_3T3R)
					raid = RATEID_IDX_BGN_3SS;
				else
				DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			}
			break;
#ifdef CONFIG_80211AC_VHT
		case WIRELESS_11_5AC:
			if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
				raid = RATEID_IDX_VHT_1SS;
			else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
				raid = RATEID_IDX_VHT_2SS;
			else if (rf_type == RF_3T3R)
				raid = RATEID_IDX_VHT_3SS;
			else
				DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			break;
		case WIRELESS_11_24AC:
			if (psta->bw_mode >= CHANNEL_WIDTH_80)
			{
				if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
					raid = RATEID_IDX_VHT_1SS;
				else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
					raid = RATEID_IDX_VHT_2SS;
				else if (rf_type == RF_3T3R)
					raid = RATEID_IDX_VHT_3SS;
				else
					DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			}
			else
			{
				if (rf_type == RF_1T1R || custom_rf_type == RF_1T2R)
					raid = RATEID_IDX_MIX1;
				else if (rf_type == RF_2T2R || custom_rf_type == RF_2T4R)
					raid = RATEID_IDX_MIX2;
				else if (rf_type == RF_3T3R)
					raid = RATEID_IDX_VHT_3SS;
				else
					DBG_871X("RF type error!(rf_type=%d)\n", rf_type);
			}
			break;
#endif
		default:
			DBG_871X("unexpected wireless mode!(psta->wireless_mode=%x)\n", psta->wireless_mode);
			break;	

	}
