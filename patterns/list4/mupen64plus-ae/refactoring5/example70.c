#ifdef DBG
if (lookup_breakpoint(((uint32_t)region << 16), 0x10000,
                          M64P_BKP_FLAG_ENABLED | M64P_BKP_FLAG_READ) != -1)
    {
        saved_readmemb[region] = read8;
        saved_readmemh[region] = read16;
        saved_readmem [region] = read32;
        saved_readmemd[region] = read64;
        readmemb[region] = readmemb_with_bp_checks;
        readmemh[region] = readmemh_with_bp_checks;
        readmem [region] = readmem_with_bp_checks;
        readmemd[region] = readmemd_with_bp_checks;
    }
    else
#endif
    {
        readmemb[region] = read8;
        readmemh[region] = read16;
        readmem [region] = read32;
        readmemd[region] = read64;
    }
