STATIC const mp_map_elem_t pyb_timer_locals_dict_table[] = {
    // instance methods
    { MP_OBJ_NEW_QSTR(MP_QSTR_init), (mp_obj_t)&pyb_timer_init_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_deinit), (mp_obj_t)&pyb_timer_deinit_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_channel), (mp_obj_t)&pyb_timer_channel_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_counter), (mp_obj_t)&pyb_timer_counter_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_prescaler), (mp_obj_t)&pyb_timer_prescaler_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_period), (mp_obj_t)&pyb_timer_period_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_callback), (mp_obj_t)&pyb_timer_callback_obj },
#if MICROPY_TIMER_REG
    { MP_OBJ_NEW_QSTR(MP_QSTR_reg), (mp_obj_t)&pyb_timer_reg_obj },
#endif
    { MP_OBJ_NEW_QSTR(MP_QSTR_UP),              MP_OBJ_NEW_SMALL_INT(FTM_COUNTERMODE_UP) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_CENTER),          MP_OBJ_NEW_SMALL_INT(FTM_COUNTERMODE_CENTER) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PWM),             MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_PWM_NORMAL) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PWM_INVERTED),    MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_PWM_INVERTED) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_OC_TIMING),       MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_OC_TIMING) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_OC_ACTIVE),       MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_OC_ACTIVE) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_OC_INACTIVE),     MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_OC_INACTIVE) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_OC_TOGGLE),       MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_OC_TOGGLE) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_IC),              MP_OBJ_NEW_SMALL_INT(CHANNEL_MODE_IC) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_HIGH),            MP_OBJ_NEW_SMALL_INT(FTM_OCPOLARITY_HIGH) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_LOW),             MP_OBJ_NEW_SMALL_INT(FTM_OCPOLARITY_LOW) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_RISING),          MP_OBJ_NEW_SMALL_INT(FTM_ICPOLARITY_RISING) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_FALLING),         MP_OBJ_NEW_SMALL_INT(FTM_ICPOLARITY_FALLING) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BOTH),            MP_OBJ_NEW_SMALL_INT(FTM_ICPOLARITY_BOTH) },
};
