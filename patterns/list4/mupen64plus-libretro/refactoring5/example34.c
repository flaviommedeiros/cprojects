#ifdef DBG
if (lookup_breakpoint(((uint32_t)region << 16), 0x10000,
            M64P_BKP_FLAG_ENABLED | M64P_BKP_FLAG_WRITE) != -1)
   {
      saved_writememb[region] = write8;
      saved_writememh[region] = write16;
      saved_writemem [region] = write32;
      saved_writememd[region] = write64;
      writememb[region] = writememb_with_bp_checks;
      writememh[region] = writememh_with_bp_checks;
      writemem [region] = writemem_with_bp_checks;
      writememd[region] = writememd_with_bp_checks;
   }
   else
#endif
   {
      writememb[region] = write8;
      writememh[region] = write16;
      writemem [region] = write32;
      writememd[region] = write64;
   }
