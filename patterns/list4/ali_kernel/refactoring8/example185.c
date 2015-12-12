static struct sysdev_attribute classic_pmc_attrs[] = {
	_SYSDEV_ATTR(pmc1, 0600, show_pmc1, store_pmc1),
	_SYSDEV_ATTR(pmc2, 0600, show_pmc2, store_pmc2),
	_SYSDEV_ATTR(pmc3, 0600, show_pmc3, store_pmc3),
	_SYSDEV_ATTR(pmc4, 0600, show_pmc4, store_pmc4),
	_SYSDEV_ATTR(pmc5, 0600, show_pmc5, store_pmc5),
	_SYSDEV_ATTR(pmc6, 0600, show_pmc6, store_pmc6),
#ifdef CONFIG_PPC64
	_SYSDEV_ATTR(pmc7, 0600, show_pmc7, store_pmc7),
	_SYSDEV_ATTR(pmc8, 0600, show_pmc8, store_pmc8),
#endif
};
