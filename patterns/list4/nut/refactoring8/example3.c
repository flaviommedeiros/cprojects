static hid_info_t mge_hid2nut[] =
{
	/* Device collection */
	/* Just declared to call *hid2info */
	{ "device.country", ST_FLAG_STRING, 20, "UPS.PowerSummary.Country", NULL, "Europe", HU_FLAG_STATIC, eaton_check_country_info },

	/* Battery page */
	{ "battery.charge", 0, 0, "UPS.PowerSummary.RemainingCapacity", NULL, "%.0f", 0, NULL },
	{ "battery.charge.low", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerSummary.RemainingCapacityLimitSetting", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "battery.charge.low", 0, 0, "UPS.PowerSummary.RemainingCapacityLimit", NULL, "%.0f", HU_FLAG_STATIC , NULL }, /* Read only */
	{ "battery.charge.restart", ST_FLAG_RW | ST_FLAG_STRING, 3, "UPS.PowerSummary.RestartLevel", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "battery.capacity", 0, 0, "UPS.BatterySystem.Battery.DesignCapacity", NULL, "%s", HU_FLAG_STATIC, mge_battery_capacity },	/* conversion needed from As to Ah */
	{ "battery.runtime", 0, 0, "UPS.PowerSummary.RunTimeToEmpty", NULL, "%.0f", 0, NULL },
	{ "battery.runtime.low", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.RemainingTimeLimit", NULL, "%.0f", 0, NULL },
	{ "battery.runtime.elapsed", 0, 0, "UPS.StatisticSystem.Input.[1].Statistic.[1].Time", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL },
	{ "battery.runtime.low", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.RemainingTimeLimit", NULL, "%.0f", 0, NULL },
	{ "battery.temperature", 0, 0, "UPS.BatterySystem.Battery.Temperature", NULL, "%s", 0, kelvin_celsius_conversion },
	{ "battery.type", 0, 0, "UPS.PowerSummary.iDeviceChemistry", NULL, "%s", HU_FLAG_STATIC, stringid_conversion },
	{ "battery.voltage", 0, 0, "UPS.BatterySystem.Voltage", NULL, "%.1f", 0, NULL },
	{ "battery.voltage", 0, 0, "UPS.PowerSummary.Voltage", NULL, "%s", 0, mge_battery_voltage },
	{ "battery.voltage.nominal", 0, 0, "UPS.BatterySystem.ConfigVoltage", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "battery.voltage.nominal", 0, 0, "UPS.PowerSummary.ConfigVoltage", NULL, "%s", HU_FLAG_STATIC, mge_battery_voltage_nominal },
	{ "battery.protection", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.BatterySystem.Battery.DeepDischargeProtection", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "battery.energysave", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].EnergySaving", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "battery.energysave.load", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].ConfigPercentLoad", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	/* Current implementation */
	{ "battery.energysave.delay", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].EnergySaving.ShutdownTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	/* Newer implementation */
	{ "battery.energysave.delay", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].ShutdownTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "battery.energysave.realpower", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].ConfigActivePower", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	/* ABM (Advanced Battery Monitoring) processing
	 * Must be processed before the BOOL status */
	/* Not published, just to store in internal var. advanced_battery_monitoring */
	{ "battery.charger.status", 0, 0, "UPS.BatterySystem.Charger.ABMEnable", NULL, "%.0f", HU_FLAG_QUICK_POLL, eaton_abm_enabled_info },
	/* Same as the one above, but for legacy units */
	/* Refer to Note 1 (This point will need more clarification!)
	{ "battery.charger.status", 0, 0, "UPS.BatterySystem.Charger.PresentStatus.Used", NULL, "%.0f", HU_FLAG_QUICK_POLL, eaton_abm_enabled_legacy_info }, */
	/* This data is the actual ABM status information */
	{ "battery.charger.status", 0, 0, "UPS.BatterySystem.Charger.Mode", NULL, "%.0f", HU_FLAG_QUICK_POLL, eaton_abm_status_info },

	/* UPS page */
	{ "ups.efficiency", 0, 0, "UPS.PowerConverter.Output.Efficiency", NULL, "%.0f", 0, NULL },
	{ "ups.firmware", 0, 0, "UPS.PowerSummary.iVersion", NULL, "%s", HU_FLAG_STATIC, stringid_conversion },
	{ "ups.load", 0, 0, "UPS.PowerSummary.PercentLoad", NULL, "%.0f", 0, NULL },
	{ "ups.load.high", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.Flow.[4].ConfigPercentLoad", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "ups.delay.start", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.DelayBeforeStartup", NULL, DEFAULT_ONDELAY, HU_FLAG_ABSENT, NULL},
	{ "ups.delay.shutdown", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.DelayBeforeShutdown", NULL, DEFAULT_OFFDELAY, HU_FLAG_ABSENT, NULL},
	{ "ups.timer.start", 0, 0, "UPS.PowerSummary.DelayBeforeStartup", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL},
	{ "ups.timer.shutdown", 0, 0, "UPS.PowerSummary.DelayBeforeShutdown", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL},
	{ "ups.timer.reboot", 0, 0, "UPS.PowerSummary.DelayBeforeReboot", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL},
	{ "ups.test.result", 0, 0, "UPS.BatterySystem.Battery.Test", NULL, "%s", 0, test_read_info },
	{ "ups.test.interval", ST_FLAG_RW | ST_FLAG_STRING, 8, "UPS.BatterySystem.Battery.TestPeriod", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "ups.beeper.status", 0 ,0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "%s", HU_FLAG_SEMI_STATIC, beeper_info },
	{ "ups.temperature", 0, 0, "UPS.PowerSummary.Temperature", NULL, "%s", 0, kelvin_celsius_conversion },
	{ "ups.power", 0, 0, "UPS.PowerConverter.Output.ApparentPower", NULL, "%.0f", 0, NULL },
	{ "ups.L1.power", 0, 0, "UPS.PowerConverter.Output.Phase.[1].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "ups.L2.power", 0, 0, "UPS.PowerConverter.Output.Phase.[2].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "ups.L3.power", 0, 0, "UPS.PowerConverter.Output.Phase.[3].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "ups.power.nominal", 0, 0, "UPS.Flow.[4].ConfigApparentPower", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "ups.realpower", 0, 0, "UPS.PowerConverter.Output.ActivePower", NULL, "%.0f", 0, NULL },
	{ "ups.L1.realpower", 0, 0, "UPS.PowerConverter.Output.Phase.[1].ActivePower", NULL, "%.0f", 0, NULL },
	{ "ups.L2.realpower", 0, 0, "UPS.PowerConverter.Output.Phase.[2].ActivePower", NULL, "%.0f", 0, NULL },
	{ "ups.L3.realpower", 0, 0, "UPS.PowerConverter.Output.Phase.[3].ActivePower", NULL, "%.0f", 0, NULL },
	{ "ups.realpower.nominal", 0, 0, "UPS.Flow.[4].ConfigActivePower", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "ups.start.auto", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[1].AutomaticRestart", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "ups.start.battery", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Input.[3].StartOnBattery", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "ups.start.reboot", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.ForcedReboot", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "ups.shutdown", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.PresentStatus.Switchable", NULL, "%s", HU_FLAG_SEMI_STATIC | HU_FLAG_ENUM, eaton_enable_disable_info },
#ifdef HAVE_STRPTIME
	{ "ups.date", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.Time", NULL, "%s", 0, mge_date_conversion },
	{ "ups.time", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerSummary.Time", NULL, "%s", 0, mge_time_conversion },
#else
	{ "ups.date", 0, 0, "UPS.PowerSummary.Time", NULL, "%s", 0, mge_date_conversion },
	{ "ups.time", 0, 0, "UPS.PowerSummary.Time", NULL, "%s", 0, mge_time_conversion },
#endif /* HAVE_STRPTIME */
	{ "ups.type", 0, 0, "UPS.PowerConverter.ConverterType", NULL, "%s", HU_FLAG_STATIC, mge_upstype_conversion },

	/* Special case: boolean values that are mapped to ups.status and ups.alarm */
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.ACPresent", NULL, NULL, HU_FLAG_QUICK_POLL, online_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[3].PresentStatus.Used", NULL, NULL, 0, mge_onbatt_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.Used", NULL, NULL, 0, online_info },
	/* These 2 ones are used when ABM is disabled */
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Discharging", NULL, NULL, HU_FLAG_QUICK_POLL, eaton_discharging_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Charging", NULL, NULL, HU_FLAG_QUICK_POLL, eaton_charging_info },
	/* And this one when ABM is enabled (same as battery.charger.status) */
	{ "BOOL", 0, 0, "UPS.BatterySystem.Charger.Mode", NULL, "%.0f", HU_FLAG_QUICK_POLL, eaton_abm_chrg_dischrg_info },
	/* FIXME: on Dell, the above requires an "AND" with "UPS.BatterySystem.Charger.Mode = 1" */
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.BelowRemainingCapacityLimit", NULL, NULL, HU_FLAG_QUICK_POLL, lowbatt_info },
	/* Output overload, Level 1 (FIXME: add the level?) */
	{ "BOOL", 0, 0, "UPS.PowerConverter.Output.Overload.[1].PresentStatus.OverThreshold", NULL, NULL, 0, overload_info },
	/* Output overload, Level 2 (FIXME: add the level?) */
	{ "BOOL", 0, 0, "UPS.PowerConverter.Output.Overload.[2].PresentStatus.OverThreshold", NULL, NULL, 0, overload_info },
	/* Output overload, Level 3 (FIXME: add the level?) */
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Overload", NULL, NULL, 0, overload_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.NeedReplacement", NULL, NULL, 0, replacebatt_info },
	/* FIXME: on Dell, the above requires an "AND" with "UPS.BatterySystem.Battery.Test = 3Â " */
	{ "BOOL", 0, 0, "UPS.LCMSystem.LCMAlarm.[2].PresentStatus.TimerExpired", NULL, NULL, 0, replacebatt_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.Buck", NULL, NULL, 0, trim_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.Boost", NULL, NULL, 0, boost_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.VoltageOutOfRange", NULL, NULL, 0, vrange_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.FrequencyOutOfRange", NULL, NULL, 0, frange_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Good", NULL, NULL, 0, off_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[2].PresentStatus.Used", NULL, NULL, 0, bypass_auto_info }, /* Automatic bypass */
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[4].PresentStatus.Used", NULL, NULL, 0, bypass_manual_info }, /* Manual bypass */
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.FanFailure", NULL, NULL, 0, fanfail_info },
	{ "BOOL", 0, 0, "UPS.BatterySystem.Battery.PresentStatus.Present", NULL, NULL, 0, nobattery_info },
	{ "BOOL", 0, 0, "UPS.BatterySystem.Charger.PresentStatus.InternalFailure", NULL, NULL, 0, chargerfail_info },
	{ "BOOL", 0, 0, "UPS.BatterySystem.Charger.PresentStatus.VoltageTooHigh", NULL, NULL, 0, battvolthi_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.VoltageTooHigh", NULL, NULL, 0, battvolthi_info },
	/* Battery DC voltage too high! */
	{ "BOOL", 0, 0, "UPS.BatterySystem.Battery.PresentStatus.VoltageTooHigh", NULL, NULL, 0, battvolthi_info },
	{ "BOOL", 0, 0, "UPS.BatterySystem.Charger.PresentStatus.VoltageTooLow", NULL, NULL, 0, battvoltlo_info },
	{ "BOOL", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.VoltageTooLow", NULL, NULL, 0, mge_onbatt_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.InternalFailure", NULL, NULL, 0, commfault_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.OverTemperature", NULL, NULL, 0, overheat_info },
	{ "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.ShutdownImminent", NULL, NULL, 0, shutdownimm_info },

	/* Vendor specific ups.alarm */
	{ "ups.alarm", 0, 0, "UPS.PowerSummary.PresentStatus.EmergencyStop", NULL, NULL, 0, mge_emergency_stop },
	{ "ups.alarm", 0, 0, "UPS.PowerConverter.Input.[1].PresentStatus.WiringFault", NULL, NULL, 0, mge_wiring_fault },
	{ "ups.alarm", 0, 0, "UPS.PowerSummary.PresentStatus.ConfigurationFailure", NULL, NULL, 0, mge_config_failure },
	{ "ups.alarm", 0, 0, "UPS.PowerConverter.Inverter.PresentStatus.VoltageTooHigh", NULL, NULL, 0, mge_inverter_volthi },
	{ "ups.alarm", 0, 0, "UPS.PowerConverter.Inverter.PresentStatus.VoltageTooLow", NULL, NULL, 0, mge_inverter_voltlo },
	{ "ups.alarm", 0, 0, "UPS.PowerConverter.Output.PresentStatus.ShortCircuit", NULL, NULL, 0, mge_short_circuit },

	/* Input page */
	{ "input.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L1-N.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[1].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L2-N.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[2].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L3-N.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[3].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L1-L2.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[12].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L2-L3.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[23].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.L3-L1.voltage", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[31].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.voltage.nominal", 0, 0, "UPS.Flow.[1].ConfigVoltage", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "input.current", 0, 0, "UPS.PowerConverter.Input.[1].Current", NULL, "%.2f", 0, NULL },
	{ "input.L1.current", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[1].Current", NULL, "%.1f", 0, NULL },
	{ "input.L2.current", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[2].Current", NULL, "%.1f", 0, NULL },
	{ "input.L3.current", 0, 0, "UPS.PowerConverter.Input.[1].Phase.[3].Current", NULL, "%.1f", 0, NULL },
	{ "input.current.nominal", 0, 0, "UPS.Flow.[1].ConfigCurrent", NULL, "%.2f", HU_FLAG_STATIC, NULL },
	{ "input.frequency", 0, 0, "UPS.PowerConverter.Input.[1].Frequency", NULL, "%.1f", 0, NULL },
	{ "input.frequency.nominal", 0, 0, "UPS.Flow.[1].ConfigFrequency", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	/* same as "input.transfer.boost.low" */
	{ "input.transfer.low", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.LowVoltageTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "input.transfer.boost.low", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.LowVoltageBoostTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "input.transfer.boost.high", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.HighVoltageBoostTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "input.transfer.trim.low", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.LowVoltageBuckTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	/* same as "input.transfer.trim.high" */
	{ "input.transfer.high", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.HighVoltageTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "input.transfer.trim.high", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.HighVoltageBuckTransfer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "input.sensitivity", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.PowerConverter.Output.SensitivityMode", NULL, "%s", HU_FLAG_SEMI_STATIC, mge_sensitivity_info },
	{ "input.voltage.extended", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.ExtendedVoltageMode", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },
	{ "input.frequency.extended", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.PowerConverter.Output.ExtendedFrequencyMode", NULL, "%s", HU_FLAG_SEMI_STATIC, yes_no_info },

	/* Bypass page */
	{ "input.bypass.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L1-N.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[1].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L2-N.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[2].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L3-N.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[3].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L1-L2.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[12].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L2-L3.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[23].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L3-L1.voltage", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[31].Voltage", NULL, "%.1f", 0, NULL },
	{ "input.bypass.voltage.nominal", 0, 0, "UPS.Flow.[2].ConfigVoltage", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "input.bypass.current", 0, 0, "UPS.PowerConverter.Input.[2].Current", NULL, "%.2f", 0, NULL },
	{ "input.bypass.L1.current", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[1].Current", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L2.current", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[2].Current", NULL, "%.1f", 0, NULL },
	{ "input.bypass.L3.current", 0, 0, "UPS.PowerConverter.Input.[2].Phase.[3].Current", NULL, "%.1f", 0, NULL },
	{ "input.bypass.current.nominal", 0, 0, "UPS.Flow.[2].ConfigCurrent", NULL, "%.2f", HU_FLAG_STATIC, NULL },
	{ "input.bypass.frequency", 0, 0, "UPS.PowerConverter.Input.[2].Frequency", NULL, "%.1f", 0, NULL },
	{ "input.bypass.frequency.nominal", 0, 0, "UPS.Flow.[2].ConfigFrequency", NULL, "%.0f", HU_FLAG_STATIC, NULL },

	/* Output page */
	{ "output.voltage", 0, 0, "UPS.PowerConverter.Output.Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L1-N.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[1].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L2-N.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[2].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L3-N.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[3].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L1-L2.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[12].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L2-L3.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[23].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.L3-L1.voltage", 0, 0, "UPS.PowerConverter.Output.Phase.[31].Voltage", NULL, "%.1f", 0, NULL },
	{ "output.voltage.nominal", ST_FLAG_RW | ST_FLAG_STRING, 3, "UPS.Flow.[4].ConfigVoltage", NULL, "%.0f", HU_FLAG_SEMI_STATIC | HU_FLAG_ENUM, nominal_output_voltage_info },
	{ "output.current", 0, 0, "UPS.PowerConverter.Output.Current", NULL, "%.2f", 0, NULL },
	{ "output.L1.current", 0, 0, "UPS.PowerConverter.Output.Phase.[1].Current", NULL, "%.1f", 0, NULL },
	{ "output.L2.current", 0, 0, "UPS.PowerConverter.Output.Phase.[2].Current", NULL, "%.1f", 0, NULL },
	{ "output.L3.current", 0, 0, "UPS.PowerConverter.Output.Phase.[3].Current", NULL, "%.1f", 0, NULL },
	{ "output.current.nominal", 0, 0, "UPS.Flow.[4].ConfigCurrent", NULL, "%.2f", 0, NULL },
	{ "output.frequency", 0, 0, "UPS.PowerConverter.Output.Frequency", NULL, "%.1f", 0, NULL },
	/* FIXME: can be RW (50/60) (or on .nominal)? */
	{ "output.frequency.nominal", 0, 0, "UPS.Flow.[4].ConfigFrequency", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "output.powerfactor", 0, 0, "UPS.PowerConverter.Output.PowerFactor", NULL, "%s", 0, mge_powerfactor_conversion },

	/* Outlet page (using MGE UPS SYSTEMS - PowerShare technology) */
	{ "outlet.id", 0, 0, "UPS.OutletSystem.Outlet.[1].OutletID", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "outlet.desc", ST_FLAG_RW | ST_FLAG_STRING, 20, "UPS.OutletSystem.Outlet.[1].OutletID", NULL, "Main Outlet", HU_FLAG_ABSENT, NULL },
	{ "outlet.switchable", 0, 0, "UPS.OutletSystem.Outlet.[1].PresentStatus.Switchable", NULL, "%s", HU_FLAG_STATIC, yes_no_info },
	/* On Protection Station, the line below is the power consumption threshold
	 * on the master outlet used to automatically power off the slave outlets.
	 * Values: 10, 25 (default) or 60 VA. */
	{ "outlet.power", ST_FLAG_RW | ST_FLAG_STRING, 6, "UPS.OutletSystem.Outlet.[1].ConfigApparentPower", NULL, "%s", HU_FLAG_SEMI_STATIC | HU_FLAG_ENUM, pegasus_threshold_info },

	{ "outlet.power", 0, 0, "UPS.OutletSystem.Outlet.[1].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "outlet.realpower", 0, 0, "UPS.OutletSystem.Outlet.[1].ActivePower", NULL, "%.0f", 0, NULL },
	{ "outlet.current", 0, 0, "UPS.OutletSystem.Outlet.[1].Current", NULL, "%.2f", 0, NULL },
	{ "outlet.powerfactor", 0, 0, "UPS.OutletSystem.Outlet.[1].PowerFactor", NULL, "%.2f", 0, NULL }, /* "%s", 0, mge_powerfactor_conversion }, */

	/* First outlet */
	{ "outlet.1.id", 0, 0, "UPS.OutletSystem.Outlet.[2].OutletID", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "outlet.1.desc", ST_FLAG_RW | ST_FLAG_STRING, 20, "UPS.OutletSystem.Outlet.[2].OutletID", NULL, "PowerShare Outlet 1", HU_FLAG_ABSENT, NULL },
	{ "outlet.1.switchable", 0, 0, "UPS.OutletSystem.Outlet.[2].PresentStatus.Switchable", NULL, "%s", HU_FLAG_STATIC, yes_no_info },
	{ "outlet.1.status", 0, 0, "UPS.OutletSystem.Outlet.[2].PresentStatus.SwitchOn/Off", NULL, "%s", 0, on_off_info },
	/* For low end models, with 1 non backup'ed outlet */
	{ "outlet.1.status", 0, 0, "UPS.PowerSummary.PresentStatus.ACPresent", NULL, "%s", 0, on_off_info },
	/* FIXME: change to outlet.1.battery.charge.low, as in mge-xml.c?! */
	{ "outlet.1.autoswitch.charge.low", ST_FLAG_RW | ST_FLAG_STRING, 3, "UPS.OutletSystem.Outlet.[2].RemainingCapacityLimit", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.1.delay.shutdown", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.OutletSystem.Outlet.[2].ShutdownTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.1.delay.start", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.OutletSystem.Outlet.[2].StartupTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.1.power", 0, 0, "UPS.OutletSystem.Outlet.[2].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "outlet.1.realpower", 0, 0, "UPS.OutletSystem.Outlet.[2].ActivePower", NULL, "%.0f", 0, NULL },
	{ "outlet.1.current", 0, 0, "UPS.OutletSystem.Outlet.[2].Current", NULL, "%.2f", 0, NULL },
	{ "outlet.1.powerfactor", 0, 0, "UPS.OutletSystem.Outlet.[2].PowerFactor", NULL, "%.2f", 0, NULL }, /* "%s", 0, mge_powerfactor_conversion }, */
	/* Second outlet */
	{ "outlet.2.id", 0, 0, "UPS.OutletSystem.Outlet.[3].OutletID", NULL, "%.0f", HU_FLAG_STATIC, NULL },
	{ "outlet.2.desc", ST_FLAG_RW | ST_FLAG_STRING, 20, "UPS.OutletSystem.Outlet.[3].OutletID", NULL, "PowerShare Outlet 2", HU_FLAG_ABSENT, NULL },
	/* needed for Pegasus to enable master/slave mode:
	 * FIXME: rename to something more suitable (outlet.?) */
	{ "outlet.2.switchable", ST_FLAG_RW | ST_FLAG_STRING, 3, "UPS.OutletSystem.Outlet.[3].PresentStatus.Switchable", NULL, "%s", HU_FLAG_SEMI_STATIC, pegasus_yes_no_info },
	/* Generic version (RO) for other models */
	{ "outlet.2.switchable", 0, 0, "UPS.OutletSystem.Outlet.[3].PresentStatus.Switchable", NULL, "%s", 0, yes_no_info },
	{ "outlet.2.status", 0, 0, "UPS.OutletSystem.Outlet.[3].PresentStatus.SwitchOn/Off", NULL, "%s", 0, on_off_info },
	{ "outlet.2.autoswitch.charge.low", ST_FLAG_RW | ST_FLAG_STRING, 3, "UPS.OutletSystem.Outlet.[3].RemainingCapacityLimit", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.2.delay.shutdown", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.OutletSystem.Outlet.[3].ShutdownTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.2.delay.start", ST_FLAG_RW | ST_FLAG_STRING, 5, "UPS.OutletSystem.Outlet.[3].StartupTimer", NULL, "%.0f", HU_FLAG_SEMI_STATIC, NULL },
	{ "outlet.2.power", 0, 0, "UPS.OutletSystem.Outlet.[3].ApparentPower", NULL, "%.0f", 0, NULL },
	{ "outlet.2.realpower", 0, 0, "UPS.OutletSystem.Outlet.[3].ActivePower", NULL, "%.0f", 0, NULL },
	{ "outlet.2.current", 0, 0, "UPS.OutletSystem.Outlet.[3].Current", NULL, "%.2f", 0, NULL },
	{ "outlet.2.powerfactor", 0, 0, "UPS.OutletSystem.Outlet.[3].PowerFactor", NULL, "%.2f", 0, NULL }, /* "%s", 0, mge_powerfactor_conversion }, */

	/* instant commands. */
	/* splited into subset while waiting for extradata support
	* ie: test.battery.start quick
	*/
	{ "test.battery.start.quick", 0, 0, "UPS.BatterySystem.Battery.Test", NULL, "1", HU_TYPE_CMD, NULL },
	{ "test.battery.start.deep", 0, 0, "UPS.BatterySystem.Battery.Test", NULL, "2", HU_TYPE_CMD, NULL },
	{ "test.battery.stop", 0, 0, "UPS.BatterySystem.Battery.Test", NULL, "3", HU_TYPE_CMD, NULL },
	{ "load.off.delay", 0, 0, "UPS.PowerSummary.DelayBeforeShutdown", NULL, DEFAULT_OFFDELAY, HU_TYPE_CMD, NULL },
	{ "load.on.delay", 0, 0, "UPS.PowerSummary.DelayBeforeStartup", NULL, DEFAULT_ONDELAY, HU_TYPE_CMD, NULL },
	{ "shutdown.stop", 0, 0, "UPS.PowerSummary.DelayBeforeShutdown", NULL, "-1", HU_TYPE_CMD, NULL },
	{ "shutdown.reboot", 0, 0, "UPS.PowerSummary.DelayBeforeReboot", NULL, "10", HU_TYPE_CMD, NULL},
	{ "beeper.off", 0, 0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "1", HU_TYPE_CMD, NULL },
	{ "beeper.on", 0, 0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "2", HU_TYPE_CMD, NULL },
	{ "beeper.mute", 0, 0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "3", HU_TYPE_CMD, NULL },
	{ "beeper.disable", 0, 0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "1", HU_TYPE_CMD, NULL },
	{ "beeper.enable", 0, 0, "UPS.PowerSummary.AudibleAlarmControl", NULL, "2", HU_TYPE_CMD, NULL },

	/* Command for the outlet collection */
	{ "outlet.1.load.off", 0, 0, "UPS.OutletSystem.Outlet.[2].DelayBeforeShutdown", NULL, "0", HU_TYPE_CMD, NULL },
	{ "outlet.1.load.on", 0, 0, "UPS.OutletSystem.Outlet.[2].DelayBeforeStartup", NULL, "0", HU_TYPE_CMD, NULL },
	{ "outlet.2.load.off", 0, 0, "UPS.OutletSystem.Outlet.[3].DelayBeforeShutdown", NULL, "0", HU_TYPE_CMD, NULL },
	{ "outlet.2.load.on", 0, 0, "UPS.OutletSystem.Outlet.[3].DelayBeforeStartup", NULL, "0", HU_TYPE_CMD, NULL },

	/* end of structure. */
	{ NULL }
};
