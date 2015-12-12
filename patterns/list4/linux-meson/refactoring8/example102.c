static struct class_attribute saradc_class_attrs[] = {
    __ATTR_RO(saradc_ch0),
    __ATTR_RO(saradc_ch1),
    __ATTR_RO(saradc_ch2),
    __ATTR_RO(saradc_ch3),
    __ATTR_RO(saradc_ch4),
    __ATTR_RO(saradc_ch5),
#ifndef CONFIG_MESON_CPU_TEMP_SENSOR
    __ATTR_RO(saradc_ch6),
    __ATTR(saradc_temperature, S_IRUGO | S_IWUSR, NULL, saradc_temperature_store),
#else
    __ATTR_RO(temperature_raw),
    __ATTR_RO(temperature),
    __ATTR(temperature_mode, S_IRUGO | S_IWUSR, temperature_mode_show, temperature_mode_store),
#endif
    __ATTR_RO(saradc_ch7),    
    __ATTR(saradc_print_flag, S_IRUGO | S_IWUSR,NULL, saradc_print_flag_store),
    __ATTR_NULL
};
