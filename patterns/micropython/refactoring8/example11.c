STATIC const mp_map_elem_t mp_constants_table[] = {
    #if MICROPY_PY_UCTYPES
    { MP_OBJ_NEW_QSTR(MP_QSTR_uctypes), (mp_obj_t)&mp_module_uctypes },
    #endif
    // Extra constants as defined by a port
    MICROPY_PORT_CONSTANTS
};
