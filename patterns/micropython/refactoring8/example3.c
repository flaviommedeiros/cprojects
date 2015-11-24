STATIC const mp_map_elem_t pyb_dac_locals_dict_table[] = {
    // instance methods
    { MP_OBJ_NEW_QSTR(MP_QSTR_init), (mp_obj_t)&pyb_dac_init_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_write), (mp_obj_t)&pyb_dac_write_obj },
    #if defined(TIM6)
    { MP_OBJ_NEW_QSTR(MP_QSTR_noise), (mp_obj_t)&pyb_dac_noise_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_triangle), (mp_obj_t)&pyb_dac_triangle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_write_timed), (mp_obj_t)&pyb_dac_write_timed_obj },
    #endif

    // class constants
    { MP_OBJ_NEW_QSTR(MP_QSTR_NORMAL),      MP_OBJ_NEW_SMALL_INT(DMA_NORMAL) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_CIRCULAR),    MP_OBJ_NEW_SMALL_INT(DMA_CIRCULAR) },
};
