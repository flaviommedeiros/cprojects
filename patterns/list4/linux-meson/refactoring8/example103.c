static struct attribute* sensetek_optical_sensors_dbg_attrs [] =
{
    &help_attribute.attr,
    &lux_range_attribute.attr,
    &lux_attribute.attr,
    &als_enable_attribute.attr,
    &als_lux_res_attribute.attr,
    &driver_version_attribute.attr,
#ifdef CONFIG_STK_ALS_TRANSMITTANCE_TUNING
    &als_transmittance_attribute.attr,
#endif
    NULL,
};
