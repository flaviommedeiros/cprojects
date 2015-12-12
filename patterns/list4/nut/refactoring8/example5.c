static hid_info_t belkin_hid2nut[] = {

  /* interpreted Belkin variables */
  { "battery.charge", 0, 0, "UPS.BELKINBatterySystem.BELKINCharge", NULL, "%.0f", 0, NULL },
  /* { "battery.charge.broken", 0, 0, "UPS.PowerSummary.RemainingCapacity", NULL, "%.0f", 0, NULL }, */
  { "battery.charge.low", 0, 0, "UPS.PowerSummary.RemainingCapacityLimit", NULL, "%.0f", 0, NULL },
  { "battery.charge.warning", 0, 0, "UPS.PowerSummary.WarningCapacityLimit", NULL, "%.0f", 0, NULL }, /* Read only */
  { "battery.runtime", 0, 0, "UPS.PowerSummary.RunTimeToEmpty", NULL, "%.0f", 0, NULL },
  { "battery.type", 0, 0, "UPS.PowerSummary.iDeviceChemistry", NULL, "%s", 0, stringid_conversion },
  { "battery.voltage", 0, 0, "UPS.BELKINBatterySystem.BELKINVoltage", NULL, "%s", 0, divide_by_10_conversion },
  { "battery.voltage.nominal", 0, 0, "UPS.BELKINConfig.BELKINConfigBatteryVoltage", NULL, "%.0f", 0, NULL },
  { "input.frequency", 0, 0, "UPS.BELKINPowerState.BELKINInput.BELKINFrequency", NULL, "%s", 0, divide_by_10_conversion },
  { "input.frequency.nominal", 0, 0, "UPS.BELKINConfig.BELKINConfigFrequency", NULL, "%.0f", 0, NULL },
  { "input.sensitivity", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.BELKINDevice.BELKINVoltageSensitivity", NULL, "%s", 0, belkin_sensitivity_conversion },
  { "input.transfer.high", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.BELKINConfig.BELKINHighVoltageTransfer", NULL, "%.0f", 0, NULL },
  { "input.transfer.high.max", 0, 0, "UPS.BELKINConfig.BELKINHighVoltageTransferMax", NULL, "%.0f", 0, NULL },
  { "input.transfer.high.min", 0, 0, "UPS.BELKINConfig.BELKINHighVoltageTransferMin", NULL, "%.0f", 0, NULL },
  { "input.transfer.low", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.BELKINConfig.BELKINLowVoltageTransfer", NULL, "%.0f", 0, NULL },
  { "input.transfer.low.max", 0, 0, "UPS.BELKINConfig.BELKINLowVoltageTransferMax", NULL, "%.0f", 0, NULL },
  { "input.transfer.low.min", 0, 0, "UPS.BELKINConfig.BELKINLowVoltageTransferMin", NULL, "%.0f", 0, NULL },
  { "input.voltage", 0, 0, "UPS.BELKINPowerState.BELKINInput.BELKINVoltage", NULL, "%s", 0, divide_by_10_conversion },
  { "input.voltage.nominal", 0, 0, "UPS.BELKINConfig.BELKINConfigVoltage", NULL, "%.0f", 0, NULL },
  { "output.frequency", 0, 0, "UPS.BELKINPowerState.BELKINOutput.BELKINFrequency", NULL, "%s", 0, divide_by_10_conversion },
  { "output.voltage", 0, 0, "UPS.BELKINPowerState.BELKINOutput.BELKINVoltage", NULL, "%s", 0, divide_by_10_conversion },
  { "ups.beeper.status", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "%s", 0, beeper_info },
  { "ups.delay.start", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.BELKINControls.BELKINDelayBeforeStartup", NULL, DEFAULT_ONDELAY, HU_FLAG_ABSENT, NULL },
  { "ups.delay.shutdown", ST_FLAG_RW | ST_FLAG_STRING, 10, "UPS.BELKINControls.BELKINDelayBeforeShutdown", NULL, DEFAULT_OFFDELAY, HU_FLAG_ABSENT, NULL },
  { "ups.timer.start", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeStartup", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL },
  { "ups.timer.shutdown", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeShutdown", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL },
  { "ups.timer.reboot", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeReboot", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL },
  { "ups.firmware", 0, 0, "UPS.BELKINDevice.BELKINUPSType", NULL, "%s", 0, belkin_firmware_conversion },
  { "ups.load", 0, 0, "UPS.BELKINPowerState.BELKINOutput.BELKINPercentLoad", NULL, "%.0f", 0, NULL },
  { "ups.load.high", 0, 0, "UPS.BELKINConfig.BELKINConfigOverloadTransfer", NULL, "%.0f", 0, NULL },
  { "ups.mfr.date", 0, 0, "UPS.PowerSummary.ManufacturerDate", NULL, "%s", 0, date_conversion },
  { "ups.power.nominal", 0, 0, "UPS.BELKINConfig.BELKINConfigApparentPower", NULL, "%.0f", 0, NULL },
  { "ups.serial", 0, 0, "UPS.PowerSummary.iSerialNumber", NULL, "%s", 0, stringid_conversion },
  { "ups.test.result", 0, 0, "UPS.BELKINControls.BELKINTest", NULL, "%s", 0, belkin_test_info },
  { "ups.type", 0, 0, "UPS.BELKINDevice.BELKINUPSType", NULL, "%s", 0, belkin_upstype_conversion },
  /* Liebert PSA: */
  { "battery.charge", 0, 0, "UPS.PowerSummary.RemainingCapacity", NULL, "%.0f", HU_FLAG_QUICK_POLL, NULL },  /* why .broken above? */
  { "input.frequency", 0, 0, "UPS.Input.Frequency", NULL, "%s", 0, divide_by_10_conversion },
  { "input.voltage", 0, 0, "UPS.Input.Voltage", NULL, "%s", 0, liebert_line_voltage_info },
  { "output.voltage", 0, 0, "UPS.Output.Voltage", NULL, "%s", 0, liebert_line_voltage_info },
  /* You would think these next two would be off by the same factor. You'd be wrong. */
  { "battery.voltage", 0, 0, "UPS.PowerSummary.Voltage", NULL, "%s", 0, liebert_line_voltage_info },
  { "battery.voltage.nominal", 0, 0, "UPS.PowerSummary.ConfigVoltage", NULL, "%s", HU_FLAG_STATIC, liebert_config_voltage_info },
  { "ups.load", 0, 0, "UPS.Output.PercentLoad", NULL, "%.0f", 0, NULL },
  /* status */
  { "BOOL", 0, 0, "UPS.PowerSummary.Discharging", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_discharging_info }, /* might not need to be liebert_* version */
  { "BOOL", 0, 0, "UPS.PowerSummary.Charging", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_charging_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.ShutdownImminent", NULL, NULL, 0, liebert_shutdownimm_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.ACPresent", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_online_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Discharging", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_discharging_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.Charging", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_charging_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.ShutdownImminent", NULL, NULL, 0, liebert_shutdownimm_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.ACPresent", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_online_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.NeedReplacement", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_replacebatt_info },
  { "BOOL", 0, 0, "UPS.PowerSummary.PresentStatus.BelowRemainingCapacityLimit", NULL, NULL, HU_FLAG_QUICK_POLL, liebert_lowbatt_info },

  /* { "BOOL", 0, 0, "UPS.PowerSummary.BelowRemainingCapacityLimit", NULL, "%s", 0, lowbatt_info }, broken! */
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINPowerStatus", NULL, NULL, 0, belkin_overload_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINPowerStatus", NULL, NULL, 0, belkin_overheat_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINPowerStatus", NULL, NULL, 0, belkin_commfault_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINPowerStatus", NULL, NULL, 0, belkin_awaitingpower_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINPowerStatus", NULL, NULL, HU_FLAG_QUICK_POLL, belkin_online_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINBatteryStatus", NULL, NULL, HU_FLAG_QUICK_POLL, belkin_depleted_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINBatteryStatus", NULL, NULL, 0, belkin_replacebatt_conversion },
  { "BOOL", 0, 0, "UPS.BELKINStatus.BELKINBatteryStatus", NULL, NULL, HU_FLAG_QUICK_POLL, belkin_lowbatt_conversion },

  /* instant commands. */
  /* split into subsets while waiting for extradata support
   * ie: test.battery.start quick
   */
  { "test.battery.start.quick", 0, 0, "UPS.BELKINControls.BELKINTest", NULL, "1", HU_TYPE_CMD, NULL },
  { "test.battery.start.deep", 0, 0, "UPS.BELKINControls.BELKINTest", NULL, "2", HU_TYPE_CMD, NULL },
  { "test.battery.stop", 0, 0, "UPS.BELKINControls.BELKINTest", NULL, "3", HU_TYPE_CMD, NULL },
  { "beeper.on", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "2", HU_TYPE_CMD, NULL },
  { "beeper.off", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "3", HU_TYPE_CMD, NULL },
  { "beeper.disable", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "1", HU_TYPE_CMD, NULL },
  { "beeper.enable", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "2", HU_TYPE_CMD, NULL },
  { "beeper.mute", 0, 0, "UPS.BELKINControls.BELKINAudibleAlarmControl", NULL, "3", HU_TYPE_CMD, NULL },
  { "load.off", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeShutdown", NULL, "1", HU_TYPE_CMD, NULL },
  { "load.on", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeStartup", NULL, "1", HU_TYPE_CMD, NULL },
  { "load.off.delay", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeShutdown", NULL, DEFAULT_OFFDELAY, HU_TYPE_CMD, NULL },
  { "load.on.delay", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeStartup", NULL, DEFAULT_ONDELAY, HU_TYPE_CMD, NULL },
  { "shutdown.stop", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeShutdown", NULL, "-1", HU_TYPE_CMD, NULL },
  { "shutdown.reboot", 0, 0, "UPS.BELKINControls.BELKINDelayBeforeReboot", NULL, "10", HU_TYPE_CMD, NULL },

  /* Note: on my Belkin UPS, there is no way to implement
     shutdown.return or load.on, even though they should exist in
     principle. Hopefully other Belkin models will be better
     designed. Fixme: fill in the appropriate instant commands.  For a
     more detailed description of the problem and a possible (but not
     yet implemented) workaround, see the belkinunv(8) man page.
     -PS 2005/08/28 */

#if 0
  /* added for debugging Liebert GXT3 : */
  { "unmapped.ups.powersummary.iserialnumber", 0, 0, "UPS.PowerSummary.iSerialNumber", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.imanufacturer", 0, 0, "UPS.PowerSummary.iManufacturer", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.ioeminformation", 0, 0, "UPS.PowerSummary.iOEMInformation", NULL, "%s", 0, stringid_conversion },
  { "unmapped.ups.powersummary.designcapacity", 0, 0, "UPS.PowerSummary.DesignCapacity", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.remainingtimelimit", 0, 0, "UPS.PowerSummary.RemainingTimeLimit", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.capacitymode", 0, 0, "UPS.PowerSummary.CapacityMode", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.rechargeable", 0, 0, "UPS.PowerSummary.Rechargeable", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.batterypresent", 0, 0, "UPS.PowerSummary.BatteryPresent", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.fullchargecapacity", 0, 0, "UPS.PowerSummary.FullChargeCapacity", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.capacitygranularity1", 0, 0, "UPS.PowerSummary.CapacityGranularity1", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.capacitygranularity2", 0, 0, "UPS.PowerSummary.CapacityGranularity2", NULL, "%.0f", 0, NULL },
  { "unmapped.ups.powersummary.iproduct", 0, 0, "UPS.PowerSummary.iProduct", NULL, "%.0f", 0, NULL },
#endif

  /* end of structure. */
  { NULL, 0, 0, NULL, NULL, NULL, 0, NULL }
};
