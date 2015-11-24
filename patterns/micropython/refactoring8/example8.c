STATIC const mp_map_elem_t mp_module_collections_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR__collections) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_namedtuple), (mp_obj_t)&mp_namedtuple_obj },
    #if MICROPY_PY_COLLECTIONS_ORDEREDDICT
    { MP_OBJ_NEW_QSTR(MP_QSTR_OrderedDict), (mp_obj_t)&mp_type_ordereddict },
    #endif
};
