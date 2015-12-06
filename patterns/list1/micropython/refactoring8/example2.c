STATIC const mp_map_elem_t mp_module_os_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR__os) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_stat), (mp_obj_t)&mod_os_stat_obj },
    #if MICROPY_PY_OS_STATVFS
    { MP_OBJ_NEW_QSTR(MP_QSTR_statvfs), (mp_obj_t)&mod_os_statvfs_obj },
    #endif
    { MP_OBJ_NEW_QSTR(MP_QSTR_system), (mp_obj_t)&mod_os_system_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_unlink),(mp_obj_t)&mod_os_unlink_obj},
    { MP_OBJ_NEW_QSTR(MP_QSTR_getenv),(mp_obj_t)&mod_os_getenv_obj},
    { MP_OBJ_NEW_QSTR(MP_QSTR_mkdir),(mp_obj_t)&mod_os_mkdir_obj},
};
