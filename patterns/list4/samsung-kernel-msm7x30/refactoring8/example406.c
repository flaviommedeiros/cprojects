static struct platform_device *pmu_devices[] = {
	&cpu_pmu_device,
#ifdef CONFIG_CPU_HAS_L2_PMU
	&l2_pmu_device,
#endif
};
