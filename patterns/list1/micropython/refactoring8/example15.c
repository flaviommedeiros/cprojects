STATIC const mp_map_elem_t pyb_timer_channel_locals_dict_table[] = {
    // instance methods
    { MP_OBJ_NEW_QSTR(MP_QSTR_callback), (mp_obj_t)&pyb_timer_channel_callback_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pulse_width), (mp_obj_t)&pyb_timer_channel_capture_compare_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_pulse_width_percent), (mp_obj_t)&pyb_timer_channel_pulse_width_percent_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_capture), (mp_obj_t)&pyb_timer_channel_capture_compare_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_compare), (mp_obj_t)&pyb_timer_channel_capture_compare_obj },
#if MICROPY_TIMER_REG
    { MP_OBJ_NEW_QSTR(MP_QSTR_reg), (mp_obj_t)&pyb_timer_channel_reg_obj },
#endif
};
