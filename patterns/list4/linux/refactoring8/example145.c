static struct freq_attr *acpi_cpufreq_attr[] = {
	&cpufreq_freq_attr_scaling_available_freqs,
	&freqdomain_cpus,
#ifdef CONFIG_X86_ACPI_CPUFREQ_CPB
	&cpb,
#endif
	NULL,
};
