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
		default:
			i = -EINVAL;
	}
