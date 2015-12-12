#ifdef TCC_TARGET_COFF
if (*(uint16_t *)(&ehdr) == COFF_C67_MAGIC) {
            ret = tcc_load_coff(s1, fd);
        } else
#endif
#ifdef TCC_TARGET_PE
        if (pe_test_res_file(&ehdr, ret)) {
            ret = pe_load_res_file(s1, fd);
        } else
#endif
        {
            /* as GNU ld, consider it is an ld script if not recognized */
        try_load_script:
            ret = tcc_load_ldscript(s1);
            if (ret < 0) {
                error_noabort("unrecognized file type");
                goto fail;
            }
        }
