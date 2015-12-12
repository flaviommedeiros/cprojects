#ifndef DEBUG
if (msm_batt_info.charging_source != NO_CHG)
#endif
	{
		if(!power_down)
		{
#ifdef BATTERY_CHECK_OVP
			pr_info("[BATT] %s: chg_type=%d, bat_status=%d, bat_adc=%d, chg_current=%d, bat_full=%d, bat_recharging=%d bat_ovp=%d,%d\n",
				__func__, msm_batt_info.charger_type, msm_batt_info.batt_health, msm_batt_info.battery_temp_adc, msm_batt_info.chg_current_adc, msm_batt_info.batt_full_check, msm_batt_info.batt_recharging, msm_batt_info.batt_ovp, msm_batt_info.batt_ovp_chg_block);
#else
			pr_info("[BATT] %s: charger_type=%d, battery_status=%d, battery_temp_adc=%d, chg_current=%d, battery_full=%d, battery_recharging=%d\n",
				__func__, msm_batt_info.charger_type, msm_batt_info.batt_health, msm_batt_info.battery_temp_adc, msm_batt_info.chg_current_adc, msm_batt_info.batt_full_check, msm_batt_info.batt_recharging);
#endif
		}
	}
