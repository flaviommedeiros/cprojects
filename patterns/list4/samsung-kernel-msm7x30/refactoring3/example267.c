switch (offset) {
#ifdef CONFIG_MAX17043_FUEL_GAUGE
	case RESET_SOC:
 		if (sscanf(buf, "%d\n", &x) == 1) {
			fg_reset_soc();	// rilactionservice.java...
			ret = count;
		}
		break;
#endif
#ifdef __BATT_TEST_DEVICE__
	case BATT_TEMP_TEST_ADC:
 		if (sscanf(buf, "%d\n", &x) == 1) {
			if (x == 0)
				temp_test_adc = 0;
			else
			{
				temp_test_adc = x;
			}
			ret = count;
		}
		break;
#endif
	case CHARGINGBLOCK_CLEAR:
 		if (sscanf(buf, "%d\n", &x) == 1) {
			pr_debug("\n[BATT] %s: chargingblock_clear -> write 0x%x\n\n", __func__, x);
			msm_batt_info.chargingblock_clear = x;
			ret = count;
		}
		break;
#ifdef EVENT_TEMPERATURE_CONTROL
	case CALL_2G_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_CALL_2G;
				msm_batt_info.call_2g_state = 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_CALL_2G;
				msm_batt_info.call_2g_state = 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! CALL_2G_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case CALL_3G_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_CALL_3G;
				msm_batt_info.call_3g_state = 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_CALL_3G;
				msm_batt_info.call_3g_state = 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! CALL_3G_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case WAP_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_WAP;
				msm_batt_info.wap_state = 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_WAP;
				msm_batt_info.wap_state = 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! WAP_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case CAMERA_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_CAMERA;
				msm_batt_info.camera_state = 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_CAMERA;
				msm_batt_info.camera_state = 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! CAMERA_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case WIFI_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_WIFI;
				msm_batt_info.wifi_state= 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_WIFI;
				msm_batt_info.wifi_state= 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! WIFI_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case BT_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_BT;
				msm_batt_info.bt_state= 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_BT;
				msm_batt_info.bt_state= 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! BT_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case GPS_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_GPS;
				msm_batt_info.gps_state= 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_GPS;
				msm_batt_info.gps_state= 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! GPS_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
	case MP3_STATE:
 		if (sscanf(buf, "%d\n", &x) == 1)
		{
			if (x == 1)
			{
				msm_batt_info.device_state |= EVT_MP3;
				msm_batt_info.mp3_state= 1;
			}
			else
			{
				msm_batt_info.device_state &= ~EVT_MP3;
				msm_batt_info.mp3_state= 0;
			}
			ret = count;
			pr_info("[BATT] %s: Changed! MP3_STATE, DEVICE_STATE = 0x%x\n", __func__, msm_batt_info.device_state);
		}
		break;
#endif
	default:
		return -EINVAL;
	}
