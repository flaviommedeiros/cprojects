static struct mfd_cell __devinitdata abx500_common_devs[] = {
#ifdef CONFIG_DEBUG_FS
	{
		.name = "ab8500-debug",
		.num_resources = ARRAY_SIZE(ab8500_debug_resources),
		.resources = ab8500_debug_resources,
	},
#endif
	{
		.name = "ab8500-sysctrl",
	},
	{
		.name = "ab8500-regulator",
	},
	{
		.name = "ab8500-gpadc",
		.num_resources = ARRAY_SIZE(ab8500_gpadc_resources),
		.resources = ab8500_gpadc_resources,
	},
	{
		.name = "ab8500-rtc",
		.num_resources = ARRAY_SIZE(ab8500_rtc_resources),
		.resources = ab8500_rtc_resources,
	},
	{
		.name = "ab8500-charger",
		.num_resources = ARRAY_SIZE(ab8500_charger_resources),
		.resources = ab8500_charger_resources,
	},
	{
		.name = "ab8500-btemp",
		.num_resources = ARRAY_SIZE(ab8500_btemp_resources),
		.resources = ab8500_btemp_resources,
	},
	{
		.name = "ab8500-fg",
		.num_resources = ARRAY_SIZE(ab8500_fg_resources),
		.resources = ab8500_fg_resources,
	},
	{
		.name = "ab8500-chargalg",
		.num_resources = ARRAY_SIZE(ab8500_chargalg_resources),
		.resources = ab8500_chargalg_resources,
	},
	{
		.name = "ab8500-acc-det",
		.num_resources = ARRAY_SIZE(ab8500_av_acc_detect_resources),
		.resources = ab8500_av_acc_detect_resources,
	},
	{
		.name = "ab8500-codec",
	},

	{
		.name = "ab8500-poweron-key",
		.num_resources = ARRAY_SIZE(ab8500_poweronkey_db_resources),
		.resources = ab8500_poweronkey_db_resources,
	},
	{
		.name = "ab8500-pwm",
		.id = 1,
	},
	{
		.name = "ab8500-pwm",
		.id = 2,
	},
	{
		.name = "ab8500-pwm",
		.id = 3,
	},
	{ .name = "ab8500-leds", },
	{
		.name = "ab8500-denc",
	},
	{
		.name = "ab8500-temp",
		.num_resources = ARRAY_SIZE(ab8500_temp_resources),
		.resources = ab8500_temp_resources,
	},
};
