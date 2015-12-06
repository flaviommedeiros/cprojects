if ((gps.fix >= GPS_FIX_3D && ins_float_inv.is_aligned
#if INS_FINV_USE_UTM
       && state.utm_initialized_f
#else
       && state.ned_initialized_f
#endif
      ) || !ins_gps_fix_once) {
    /* Ev = (V - YV)   */
    VECT3_DIFF(Ev, _ins->state.speed, _ins->meas.speed_gps);
    /* Ex = (X - YX)  */
    VECT3_DIFF(Ex, _ins->state.pos, _ins->meas.pos_gps);
  } else {
    FLOAT_VECT3_ZERO(Ev);
    FLOAT_VECT3_ZERO(Ex);
  }
