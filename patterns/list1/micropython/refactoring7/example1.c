return MP_OBJ_IS_TYPE(o, &mp_type_set)
#if MICROPY_PY_BUILTINS_FROZENSET
        || MP_OBJ_IS_TYPE(o, &mp_type_frozenset)
#endif
    ;
