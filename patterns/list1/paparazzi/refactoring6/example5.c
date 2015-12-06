if ((pprz_mode != PPRZ_MODE_HOME &&
       pprz_mode != PPRZ_MODE_GPS_OUT_OF_ORDER)
#ifdef UNLOCKED_HOME_MODE
      || TRUE
#endif
     ) {
#ifndef RADIO_AUTO_MODE
    return ModeUpdate(pprz_mode, PPRZ_MODE_OF_PULSE(fbw_state->channels[RADIO_MODE]));
#else
    INFO("Using RADIO_AUTO_MODE to switch between AUTO1 and AUTO2.")
    /* If RADIO_AUTO_MODE is enabled mode swithing will be seperated between two switches/channels
     * RADIO_MODE will switch between PPRZ_MODE_MANUAL and any PPRZ_MODE_AUTO mode selected by RADIO_AUTO_MODE.
     *
     * This is mainly a cludge for entry level radios with no three-way switch but two available two-way switches which can be used.
     */
    if (PPRZ_MODE_OF_PULSE(fbw_state->channels[RADIO_MODE]) == PPRZ_MODE_MANUAL) {
      /* RADIO_MODE in MANUAL position */
      return ModeUpdate(pprz_mode, PPRZ_MODE_MANUAL);
    } else {
      /* RADIO_MODE not in MANUAL position.
       * Select AUTO mode bassed on RADIO_AUTO_MODE channel
       */
      return ModeUpdate(pprz_mode, (fbw_state->channels[RADIO_AUTO_MODE] > THRESHOLD2) ? PPRZ_MODE_AUTO2 : PPRZ_MODE_AUTO1);
    }
#endif // RADIO_AUTO_MODE
  } else {
    return FALSE;
  }
