#if CALLBACK_MAX_SLOT
if (top >= CALLBACK_MAX_SLOT)
#endif
    lj_err_caller(cts->L, LJ_ERR_FFI_CBACKOV);
