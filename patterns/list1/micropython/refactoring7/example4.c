return arg_looks_integer(arg)
#if MICROPY_PY_BUILTINS_FLOAT
        || mp_obj_is_float(arg)
#endif
    ;
