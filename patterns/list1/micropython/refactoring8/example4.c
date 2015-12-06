STATIC const mp_map_elem_t adc_all_locals_dict_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR_read_channel),   (mp_obj_t)&adc_all_read_channel_obj},
    { MP_OBJ_NEW_QSTR(MP_QSTR_read_core_temp), (mp_obj_t)&adc_all_read_core_temp_obj},
#if MICROPY_PY_BUILTINS_FLOAT
    { MP_OBJ_NEW_QSTR(MP_QSTR_read_core_vbat), (mp_obj_t)&adc_all_read_core_vbat_obj},
    { MP_OBJ_NEW_QSTR(MP_QSTR_read_core_vref), (mp_obj_t)&adc_all_read_core_vref_obj},
#endif
};
