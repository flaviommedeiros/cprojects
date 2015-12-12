switch(subcmd)
	{
	case MP_START:
			DBG_871X("set case mp_start \n");
			rtw_mp_start (dev,info,wrqu,extra);
			 break; 
			 
	case MP_STOP:
			DBG_871X("set case mp_stop \n");
			rtw_mp_stop (dev,info,wrqu,extra);
			 break; 
			 
	case MP_BANDWIDTH:
			DBG_871X("set case mp_bandwidth \n");
			rtw_mp_bandwidth (dev,info,wrqu,extra);
			break;
				
	case MP_RESET_STATS:
			DBG_871X("set case MP_RESET_STATS \n");
			rtw_mp_reset_stats	(dev,info,wrqu,extra);
			break;
	case MP_SetRFPathSwh:		
			DBG_871X("set MP_SetRFPathSwitch \n");
			rtw_mp_SetRFPath  (dev,info,wdata,extra);
			break;
	case CTA_TEST:
			DBG_871X("set CTA_TEST\n");
			rtw_cta_test_start (dev, info, wdata, extra);
			break;
	case MP_DISABLE_BT_COEXIST:
			DBG_871X("set case MP_DISABLE_BT_COEXIST \n");
			rtw_mp_disable_bt_coexist(dev, info, wdata, extra);
		break;
#ifdef CONFIG_WOWLAN
	case MP_WOW_ENABLE:
			DBG_871X("set case MP_WOW_ENABLE: %s \n", extra);
			rtw_wowlan_ctrl(dev, info, wdata, extra);
	break;
#endif
#ifdef CONFIG_AP_WOWLAN
	case MP_AP_WOW_ENABLE:
			DBG_871X("set case MP_AP_WOW_ENABLE: %s \n", extra);
			rtw_ap_wowlan_ctrl(dev, info, wdata, extra);
	break;
#endif
	}
