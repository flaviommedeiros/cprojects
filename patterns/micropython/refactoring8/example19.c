STATIC const mp_map_elem_t machine_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__),            MP_OBJ_NEW_QSTR(MP_QSTR_machine) },

    { MP_OBJ_NEW_QSTR(MP_QSTR_reset),               (mp_obj_t)&machine_reset_obj },
#ifdef DEBUG
    { MP_OBJ_NEW_QSTR(MP_QSTR_info),                (mp_obj_t)&machine_info_obj },
#endif
    { MP_OBJ_NEW_QSTR(MP_QSTR_freq),                (mp_obj_t)&machine_freq_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_unique_id),           (mp_obj_t)&machine_unique_id_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_main),                (mp_obj_t)&machine_main_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_rng),                 (mp_obj_t)&machine_rng_get_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_idle),                (mp_obj_t)&machine_idle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_sleep),               (mp_obj_t)&machine_sleep_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_deepsleep),           (mp_obj_t)&machine_deepsleep_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_reset_cause),         (mp_obj_t)&machine_reset_cause_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_wake_reason),         (mp_obj_t)&machine_wake_reason_obj },

    { MP_OBJ_NEW_QSTR(MP_QSTR_disable_irq),         (mp_obj_t)&pyb_disable_irq_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_enable_irq),          (mp_obj_t)&pyb_enable_irq_obj },

    { MP_OBJ_NEW_QSTR(MP_QSTR_RTC),                 (mp_obj_t)&pyb_rtc_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Pin),                 (mp_obj_t)&pin_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ADC),                 (mp_obj_t)&pyb_adc_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_I2C),                 (mp_obj_t)&pyb_i2c_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SPI),                 (mp_obj_t)&pyb_spi_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_UART),                (mp_obj_t)&pyb_uart_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_Timer),               (mp_obj_t)&pyb_timer_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_WDT),                 (mp_obj_t)&pyb_wdt_type },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SD),                  (mp_obj_t)&pyb_sd_type },

    // class constants
    { MP_OBJ_NEW_QSTR(MP_QSTR_IDLE),                MP_OBJ_NEW_SMALL_INT(PYB_PWR_MODE_ACTIVE) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SLEEP),               MP_OBJ_NEW_SMALL_INT(PYB_PWR_MODE_LPDS) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_DEEPSLEEP),           MP_OBJ_NEW_SMALL_INT(PYB_PWR_MODE_HIBERNATE) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_POWER_ON),            MP_OBJ_NEW_SMALL_INT(PYB_SLP_PWRON_RESET) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_HARD_RESET),          MP_OBJ_NEW_SMALL_INT(PYB_SLP_HARD_RESET) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_WDT_RESET),           MP_OBJ_NEW_SMALL_INT(PYB_SLP_WDT_RESET) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_DEEPSLEEP_RESET),     MP_OBJ_NEW_SMALL_INT(PYB_SLP_HIB_RESET) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SOFT_RESET),          MP_OBJ_NEW_SMALL_INT(PYB_SLP_SOFT_RESET) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_WLAN_WAKE),           MP_OBJ_NEW_SMALL_INT(PYB_SLP_WAKED_BY_WLAN) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_PIN_WAKE),            MP_OBJ_NEW_SMALL_INT(PYB_SLP_WAKED_BY_GPIO) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_RTC_WAKE),            MP_OBJ_NEW_SMALL_INT(PYB_SLP_WAKED_BY_RTC) },
};
