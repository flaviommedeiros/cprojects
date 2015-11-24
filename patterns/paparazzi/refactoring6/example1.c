if (distance < INS_SONAR_MAX_RANGE && distance > INS_SONAR_MIN_RANGE
#ifdef INS_SONAR_THROTTLE_THRESHOLD
      && stabilization_cmd[COMMAND_THRUST] < INS_SONAR_THROTTLE_THRESHOLD
#endif
#ifdef INS_SONAR_BARO_THRESHOLD
      && ins_int.baro_z > -INS_SONAR_BARO_THRESHOLD /* z down */
#endif
      && ins_int.update_on_agl
      && ins_int.baro_initialized) {
    vff_update_z_conf(-(distance), VFF_R_SONAR_0 + VFF_R_SONAR_OF_M * fabsf(distance));
    last_offset = vff.offset;
  } else {
    /* update offset with last value to avoid divergence */
    vff_update_offset(last_offset);
  }
