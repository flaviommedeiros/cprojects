STATIC const mp_map_elem_t esp_module_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_esp) },

    { MP_OBJ_NEW_QSTR(MP_QSTR_mac), (mp_obj_t)&esp_mac_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_getaddrinfo), (mp_obj_t)&esp_getaddrinfo_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_wifi_mode), (mp_obj_t)&esp_wifi_mode_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_phy_mode), (mp_obj_t)&esp_phy_mode_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_sleep_type), (mp_obj_t)&esp_sleep_type_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_deepsleep), (mp_obj_t)&esp_deepsleep_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_flash_id), (mp_obj_t)&esp_flash_id_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_socket), (mp_obj_t)&esp_socket_type },

#if MODESP_INCLUDE_CONSTANTS
    { MP_OBJ_NEW_QSTR(MP_QSTR_MODE_11B),
        MP_OBJ_NEW_SMALL_INT(PHY_MODE_11B) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MODE_11G),
        MP_OBJ_NEW_SMALL_INT(PHY_MODE_11G) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MODE_11N),
        MP_OBJ_NEW_SMALL_INT(PHY_MODE_11N) },

    { MP_OBJ_NEW_QSTR(MP_QSTR_SLEEP_NONE),
        MP_OBJ_NEW_SMALL_INT(NONE_SLEEP_T) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SLEEP_LIGHT),
        MP_OBJ_NEW_SMALL_INT(LIGHT_SLEEP_T) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SLEEP_MODEM),
        MP_OBJ_NEW_SMALL_INT(MODEM_SLEEP_T) },

    { MP_OBJ_NEW_QSTR(MP_QSTR_STA_MODE),
        MP_OBJ_NEW_SMALL_INT(STATION_MODE)},
    { MP_OBJ_NEW_QSTR(MP_QSTR_AP_MODE),
        MP_OBJ_NEW_SMALL_INT(SOFTAP_MODE)},
    { MP_OBJ_NEW_QSTR(MP_QSTR_STA_AP_MODE),
        MP_OBJ_NEW_SMALL_INT(STATIONAP_MODE)},
#endif
};
