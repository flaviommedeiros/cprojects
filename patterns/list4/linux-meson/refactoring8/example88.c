static struct class_attribute smc_class_attrs[] = {
	__ATTR(smc_gpio_pull,  S_IRUGO | S_IWUSR, show_gpio_pull,    set_gpio_pull),
	__ATTR(ctrl_5v3v,      S_IRUGO | S_IWUSR, show_5v3v,         store_5v3v),
	__ATTR(freq,           S_IRUGO | S_IWUSR, show_freq,		 store_freq),
#ifdef MEM_DEBUG
	__ATTR(debug,          S_IRUGO | S_IWUSR, show_debug,        store_debug),
#endif
    __ATTR_NULL
};
