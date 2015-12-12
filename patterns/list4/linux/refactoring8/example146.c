struct freq_attr *cpufreq_generic_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
#ifdef CONFIG_CPU_FREQ_BOOST_SW
	&cpufreq_freq_attr_scaling_boost_freqs,
#endif
	NULL,
};
