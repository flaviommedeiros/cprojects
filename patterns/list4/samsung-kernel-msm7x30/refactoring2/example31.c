#ifndef DEBUG
if (msm_batt_info.charging_source != NO_CHG)
#endif
	{
#ifdef EVENT_TEMPERATURE_CONTROL
		{
			switch (charger_status)
			{
				case CHARGER_STATUS_GOOD: { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_STATUS_MASK) | DRVINFO_CHARGER_STATUS_GOOD;    } break;
				case CHARGER_STATUS_BAD:  { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_STATUS_MASK) | DRVINFO_CHARGER_STATUS_BAD;     } break;
				case CHARGER_STATUS_WEAK: { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_STATUS_MASK) | DRVINFO_CHARGER_STATUS_WEAK;    } break;
				default:                  { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_STATUS_MASK) | DRVINFO_CHARGER_STATUS_INVALID; } break;
			}
			switch (charger_type)
			{
				case CHARGER_TYPE_NONE:       { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_TYPE_MASK) | DRVINFO_CHARGER_TYPE_NONE;    } break;
				case CHARGER_TYPE_USB_WALL:   { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_TYPE_MASK) | DRVINFO_CHARGER_TYPE_WALL;    } break;
				case CHARGER_TYPE_USB_PC:     { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_TYPE_MASK) | DRVINFO_CHARGER_TYPE_USB_PC;  } break;
				case CHARGER_TYPE_USB_CARKIT: { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_TYPE_MASK) | DRVINFO_CHARGER_TYPE_CARKIT;  } break;
				default:                      { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGER_TYPE_MASK) | DRVINFO_CHARGER_TYPE_INVALID; } break;
			}
			switch (battery_status)
			{
				case BATTERY_STATUS_GOOD:     { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_BATTERY_STATUS_MASK) | DRVINFO_BATTERY_STATUS_GOOD;    } break;
				case BATTERY_STATUS_BAD_TEMP: { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_BATTERY_STATUS_MASK) | DRVINFO_BATTERY_STATUS_BAD_TEMP;    } break;
				case BATTERY_STATUS_BAD:      { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_BATTERY_STATUS_MASK) | DRVINFO_BATTERY_STATUS_BAD;  } break;
				case BATTERY_STATUS_REMOVED:  { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_BATTERY_STATUS_MASK) | DRVINFO_BATTERY_STATUS_REMOVED;    } break;
				default:                      { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_BATTERY_STATUS_MASK) | DRVINFO_BATTERY_STATUS_INVALID; } break;
			}
			switch (msm_batt_info.batt_status)
			{
				case POWER_SUPPLY_STATUS_CHARGING:
				{
					if (msm_batt_info.batt_recharging==1)
						msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_RECHARGING;
					else
						msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_CHARGING;
				}
					break;
				case POWER_SUPPLY_STATUS_NOT_CHARGING: { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_NOT_CHARGING; } break;
				case POWER_SUPPLY_STATUS_DISCHARGING:  { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_DIS_CHARGING; } break;
				case POWER_SUPPLY_STATUS_FULL:         { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_FULL;         } break;
				default:                               { msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_CHARGING_PHASE_MASK) | DRVINFO_CHARGING_PHASE_INVALID;      } break;
			}
			if ( BATT_DRV_VER )
			{
				msm_batt_info.driver_info = (msm_batt_info.driver_info & ~DRVINFO_VER_MASK) | (BATT_DRV_VER << 24);
			}
		}

        if(!power_down)
		{
#ifdef BATTERY_CHECK_OVP
		pr_info("[BATT] mode= %s, chgr_type=%s, batt_status=%s, batt_volt=%d%s, batt_capacity=%d%%, chg_phase=%s, temp_adc=%d(%d), curr_adc=%d, wc_adc=%d, device_state=0x%x, driver_info=0x%x, bat_ovp=%d,%d\n",
			(charging_boot == 1)?"PWR-OFF":"PWR-ON",
			(msm_batt_info.charger_type==CHARGER_TYPE_NONE)?"NONE":(msm_batt_info.charger_type==CHARGER_TYPE_WALL)?"WALL":(msm_batt_info.charger_type==CHARGER_TYPE_USB_PC)?"USB_PC":(msm_batt_info.charger_type==CHARGER_TYPE_USB_WALL)?"USB_WALL":(msm_batt_info.charger_type==CHARGER_TYPE_USB_CARKIT)?"USB_CARKIT":"INVALID",
			(msm_batt_info.batt_health==BATTERY_STATUS_GOOD)?"OK":(msm_batt_info.batt_health==BATTERY_STATUS_BAD_TEMP)?"TEMP":(msm_batt_info.batt_health==BATTERY_STATUS_BAD)?"BAD":(msm_batt_info.batt_health==BATTERY_STATUS_REMOVED)?"REMOVED":"INVALID",
			msm_batt_info.battery_voltage,
			msm_batt_info.batt_capacity,
			((msm_batt_info.batt_status==POWER_SUPPLY_STATUS_CHARGING)&&(msm_batt_info.batt_recharging==1))?"RE-CHARGING": \
				((msm_batt_info.batt_status==POWER_SUPPLY_STATUS_CHARGING)&&(msm_batt_info.batt_recharging==0))?"CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_NOT_CHARGING)?"NOT-CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_DISCHARGING)?"DIS-CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_FULL)?"FULL": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_UNKNOWN)?"UNKNOWN":"INVALID",
			msm_batt_info.battery_temp_adc,
			msm_batt_info.battery_temp,
			msm_batt_info.chg_current_adc,
			msm_batt_info.wc_adc,
			msm_batt_info.device_state,
			msm_batt_info.driver_info,  msm_batt_info.batt_ovp_chg_block);
#else
		pr_info("[BATT] mode= %s, chgr_type=%s, batt_status=%s, batt_volt=%d%s, batt_capacity=%d%%, chg_phase=%s, temp_adc=%d(%d), curr_adc=%d, wc_adc=%d, device_state=0x%x, driver_info=0x%x\n",
			(charging_boot == 1)?"PWR-OFF":"PWR-ON",
			(msm_batt_info.charger_type==CHARGER_TYPE_NONE)?"NONE":(msm_batt_info.charger_type==CHARGER_TYPE_WALL)?"WALL":(msm_batt_info.charger_type==CHARGER_TYPE_USB_PC)?"USB_PC":(msm_batt_info.charger_type==CHARGER_TYPE_USB_WALL)?"USB_WALL":(msm_batt_info.charger_type==CHARGER_TYPE_USB_CARKIT)?"USB_CARKIT":"INVALID",
			(msm_batt_info.batt_health==BATTERY_STATUS_GOOD)?"OK":(msm_batt_info.batt_health==BATTERY_STATUS_BAD_TEMP)?"TEMP":(msm_batt_info.batt_health==BATTERY_STATUS_BAD)?"BAD":(msm_batt_info.batt_health==BATTERY_STATUS_REMOVED)?"REMOVED":"INVALID",
			msm_batt_info.battery_voltage,
			msm_batt_info.batt_capacity,
			((msm_batt_info.batt_status==POWER_SUPPLY_STATUS_CHARGING)&&(msm_batt_info.batt_recharging==1))?"RE-CHARGING": \
				((msm_batt_info.batt_status==POWER_SUPPLY_STATUS_CHARGING)&&(msm_batt_info.batt_recharging==0))?"CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_NOT_CHARGING)?"NOT-CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_DISCHARGING)?"DIS-CHARGING": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_FULL)?"FULL": \
				(msm_batt_info.batt_status==POWER_SUPPLY_STATUS_UNKNOWN)?"UNKNOWN":"INVALID",
			msm_batt_info.battery_temp_adc,
			msm_batt_info.battery_temp,
			msm_batt_info.chg_current_adc,
			msm_batt_info.wc_adc,
			msm_batt_info.device_state,
			msm_batt_info.driver_info);
#endif
		}
#else
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
#endif

}
