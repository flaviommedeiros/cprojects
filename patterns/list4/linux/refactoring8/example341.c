static struct cpuidle_driver tegra_idle_driver = {
	.name = "tegra_idle",
	.owner = THIS_MODULE,
	.state_count = TEGRA114_MAX_STATES,
	.states = {
		[0] = ARM_CPUIDLE_WFI_STATE_PWR(600),
#ifdef CONFIG_PM_SLEEP
		[1] = {
			.enter			= tegra114_idle_power_down,
			.enter_freeze		= tegra114_idle_enter_freeze,
			.exit_latency		= 500,
			.target_residency	= 1000,
			.flags			= CPUIDLE_FLAG_TIMER_STOP,
			.power_usage		= 0,
			.name			= "powered-down",
			.desc			= "CPU power gated",
		},
#endif
	},
};
