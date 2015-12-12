static struct class_attribute i2c_class_attrs[] = {
    __ATTR(speed, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
    __ATTR(mode, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
    __ATTR(debug, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
    __ATTR(slave, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
    __ATTR(i2c_bus_status, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
#ifdef ENABLE_GPIO_TRIGGER
    __ATTR(trig_gpio, S_IRUGO|S_IWUSR, show_aml_i2c, store_aml_i2c),
#endif
    __ATTR_NULL
};
