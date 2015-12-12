static struct attribute *yas_acc_attributes[] = {
    &dev_attr_enable.attr,
    &dev_attr_delay.attr,
    &dev_attr_offset.attr,
    &dev_attr_position.attr,
    &dev_attr_threshold.attr,
    &dev_attr_filter_enable.attr,
    &dev_attr_wake.attr,
    &dev_attr_data.attr,
#if DEBUG
    &dev_attr_debug_reg.attr,
    &dev_attr_debug_suspend.attr,
#endif /* DEBUG */
   &dev_attr_calibration.attr,
    NULL
};
