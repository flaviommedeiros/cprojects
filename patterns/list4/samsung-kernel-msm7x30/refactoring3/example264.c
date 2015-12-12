switch (offset) {
#ifdef CONFIG_MAX17043_FUEL_GAUGE
		case FG_SOC:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				get_level_from_fuelgauge());
			break;
		case RESET_SOC :
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				fg_reset_soc());
			break;
#endif
		case BATT_TEMP_CHECK:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				msm_batt_info.batt_temp_check);
			break;
		case CHARGING_SOURCE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				msm_batt_info.charging_source);
			break;
		case BATT_CHG_CURRENT: // ICHG ADC code (charging current)
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				msm_batt_info.chg_current_adc);
			break;
#ifdef __BATT_TEST_DEVICE__
		case BATT_TEMP_TEST_ADC:
				i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n", temp_test_adc);
			break;
#endif
#ifdef CONFIG_WIRELESS_CHARGING
		case WC_STATUS:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				msm_batt_info.batt_wireless);
			break;
		case WC_ADC:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
				msm_batt_info.wc_adc);
			break;
#endif
		case CHARGINGBLOCK_CLEAR:
			i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n", msm_batt_info.chargingblock_clear);
			break;

#ifdef BATTERY_CHECK_OVP
        case BATT_OVP_STATUS:
            i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
                msm_batt_info.batt_ovp);
            break;

        case BATT_OVP_CHG_STATUS:
            i += scnprintf(buf + i, PAGE_SIZE - i, "%d\n",
                msm_batt_info.batt_ovp_chg_block);
            break;
#endif

#ifdef EVENT_TEMPERATURE_CONTROL
		case CALL_2G_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.call_2g_state);
			break;
		case CALL_3G_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.call_3g_state);
			break;
		case WAP_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.wap_state);
			break;
		case CAMERA_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.camera_state);
			break;
		case WIFI_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.wifi_state);
			break;
		case BT_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.bt_state);
			break;
		case GPS_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.gps_state);
			break;
		case MP3_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.mp3_state);
			break;
		case DEVICE_STATE:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.device_state);
			break;
		case DRIVER_INFO:
			i += scnprintf(buf + i, PAGE_SIZE - i, "0x%08x\n", msm_batt_info.driver_info);
			break;
#endif
		default:
			i = -EINVAL;
	}
