status_code tcc_set_pattern(
    const struct tcc_module *const module_inst,
    const uint32_t line_index,
    const enum tcc_output_pattern pattern)
{
    /* Sanity check arguments */
    Assert(module_inst);
    Assert(module_inst->hw);

    /* Get a pointer to the module's hardware instance */
    Tcc *const tcc_module = module_inst->hw;
    /* Get a index of the module */
    uint8_t module_index = _tcc_get_inst_index(tcc_module);
    /* Get number of output lines */
    uint8_t ow_num = _tcc_ow_nums[module_index];

    /* Check if line number is OK */
    if (line_index >= ow_num) {
        return STATUS_ERR_INVALID_ARG;
    }

    uint32_t patt_value;

    while(tcc_module->SYNCBUSY.reg  & TCC_SYNCBUSY_PATT) {
        /* Sync wait */
    }
    patt_value = tcc_module->PATT.reg;
    if (TCC_OUTPUT_PATTERN_DISABLE == pattern) {
        patt_value &= ~(TCC_PATT_PGE0 << line_index);
    } else if (TCC_OUTPUT_PATTERN_0 == pattern) {
        patt_value &= ~(TCC_PATT_PGV0 << line_index);
        patt_value |=  (TCC_PATT_PGE0 << line_index);
    } else {
        patt_value |=  ((TCC_PATT_PGE0 | TCC_PATT_PGV0) << line_index);
    }

    if (module_inst->double_buffering_enabled) {
#if (SAML21) || (SAMC20) || (SAMC21)
        tcc_module->PATTBUF.reg = patt_value;
#else
        while(tcc_module->SYNCBUSY.reg  & TCC_SYNCBUSY_PATTB) {
            /* Sync wait */
        }
        tcc_module->PATTB.reg = patt_value;
#endif
    } else {
        tcc_module->PATT.reg = patt_value;
    }
    return STATUS_OK;
}
