#ifdef IDCT_SCALING_SUPPORTED
if (!cinfo->tile_decode)
#endif
    if (cinfo->global_state != DSTATE_READY)
      ERREXIT1(cinfo, JERR_BAD_STATE, cinfo->global_state);
