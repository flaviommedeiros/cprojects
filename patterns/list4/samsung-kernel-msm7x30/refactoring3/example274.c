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
	default:
		return -EINVAL;
	}
