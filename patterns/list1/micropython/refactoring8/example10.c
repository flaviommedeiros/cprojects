const qstr mp_unary_op_method_name[] = {
    [MP_UNARY_OP_BOOL] = MP_QSTR___bool__,
    [MP_UNARY_OP_LEN] = MP_QSTR___len__,
    [MP_UNARY_OP_HASH] = MP_QSTR___hash__,
    #if MICROPY_PY_ALL_SPECIAL_METHODS
    [MP_UNARY_OP_POSITIVE] = MP_QSTR___pos__,
    [MP_UNARY_OP_NEGATIVE] = MP_QSTR___neg__,
    [MP_UNARY_OP_INVERT] = MP_QSTR___invert__,
    #endif
    [MP_UNARY_OP_NOT] = MP_QSTR_, // don't need to implement this, used to make sure array has full size
};
