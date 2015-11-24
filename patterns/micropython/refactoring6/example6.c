if (
#if !MICROPY_PY_BUILTINS_STR_UNICODE
        // It's simple - unicode is slow, non-unicode is fast
        MP_OBJ_IS_STR(o_in) ||
#endif
        MP_OBJ_IS_TYPE(o_in, &mp_type_bytes)) {
        GET_STR_LEN(o_in, l);
        return MP_OBJ_NEW_SMALL_INT(l);
    } else {
        mp_obj_type_t *type = mp_obj_get_type(o_in);
        if (type->unary_op != NULL) {
            return type->unary_op(MP_UNARY_OP_LEN, o_in);
        } else {
            return MP_OBJ_NULL;
        }
    }
