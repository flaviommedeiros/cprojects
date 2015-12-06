#ifndef DISABLE_ALIGNEMENT
if (ahrs.status == AHRS_UNINIT) {
    ahrs_aligner_run();
    if (ahrs_aligner.status == AHRS_ALIGNER_LOCKED) {
      ahrs_align();
    }
  } else {
#endif /* DISABLE_ALIGNEMENT */
    ahrs_propagate(aos.dt);
    ahrs_update_accel();

#ifndef DISABLE_MAG_UPDATE
    ahrs_update_mag();
#endif


#if AHRS_USE_GPS_HEADING

#if AHRS_TYPE == AHRS_TYPE_ICQ
    int32_t heading = ANGLE_BFP_OF_REAL(aos.heading_meas);
#endif
#if AHRS_TYPE == AHRS_TYPE_FCQ
    float heading = aos.heading_meas;
#endif

#if AHRS_TYPE == AHRS_TYPE_FCR
    ahrs_impl.gps_course = aos.heading_meas;
    ahrs_impl.gps_course_valid = TRUE;
#else
    if (aos.time > 10) {
      if (!ahrs_impl.heading_aligned) {
        ahrs_realign_heading(heading);
      } else {
        RunOnceEvery(100, ahrs_update_heading(heading));
      }
    }
#endif

#endif // AHRS_USE_GPS_HEADING

#ifndef DISABLE_ALIGNEMENT
  }
