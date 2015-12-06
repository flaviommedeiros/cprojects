switch (msg_id) {

    case DL_PING: {
      DOWNLINK_SEND_PONG(DefaultChannel, DefaultDevice);
    }
    break;

#ifdef TRAFFIC_INFO
    case DL_ACINFO: {
      if (DL_ACINFO_ac_id(dl_buffer) == AC_ID) { break; }
      uint8_t id = DL_ACINFO_ac_id(dl_buffer);
      float ux = MOfCm(DL_ACINFO_utm_east(dl_buffer));
      float uy = MOfCm(DL_ACINFO_utm_north(dl_buffer));
      float a = MOfCm(DL_ACINFO_alt(dl_buffer));
      float c = RadOfDeg(((float)DL_ACINFO_course(dl_buffer)) / 10.);
      float s = MOfCm(DL_ACINFO_speed(dl_buffer));
      float cl = MOfCm(DL_ACINFO_climb(dl_buffer));
      uint32_t t = DL_ACINFO_itow(dl_buffer);
      SetAcInfo(id, ux, uy, c, a, s, cl, t);
    }
    break;
#endif

#ifdef NAV
    case DL_MOVE_WP: {
      if (DL_MOVE_WP_ac_id(dl_buffer) != AC_ID) { break; }
      uint8_t wp_id = DL_MOVE_WP_wp_id(dl_buffer);
      float a = MOfMM(DL_MOVE_WP_alt(dl_buffer));

      /* Computes from (lat, long) in the referenced UTM zone */
      struct LlaCoor_f lla;
      lla.lat = RadOfDeg((float)(DL_MOVE_WP_lat(dl_buffer) / 1e7));
      lla.lon = RadOfDeg((float)(DL_MOVE_WP_lon(dl_buffer) / 1e7));
      struct UtmCoor_f utm;
      utm.zone = nav_utm_zone0;
      utm_of_lla_f(&utm, &lla);
      nav_move_waypoint(wp_id, utm.east, utm.north, a);

      /* Waypoint range is limited. Computes the UTM pos back from the relative
         coordinates */
      utm.east = waypoints[wp_id].x + nav_utm_east0;
      utm.north = waypoints[wp_id].y + nav_utm_north0;
      DOWNLINK_SEND_WP_MOVED(DefaultChannel, DefaultDevice, &wp_id, &utm.east, &utm.north, &a, &nav_utm_zone0);
    }
    break;

    case DL_BLOCK: {
      if (DL_BLOCK_ac_id(dl_buffer) != AC_ID) { break; }
      nav_goto_block(DL_BLOCK_block_id(dl_buffer));
      SEND_NAVIGATION(&(DefaultChannel).trans_tx, &(DefaultDevice).device);
    }
    break;
#endif /** NAV */


#ifdef WIND_INFO
    case DL_WIND_INFO: {
      if (DL_WIND_INFO_ac_id(dl_buffer) != AC_ID) { break; }
      struct FloatVect2 wind;
      wind.x = DL_WIND_INFO_north(dl_buffer);
      wind.y = DL_WIND_INFO_east(dl_buffer);
      stateSetHorizontalWindspeed_f(&wind);
#if !USE_AIRSPEED
      stateSetAirspeed_f(DL_WIND_INFO_airspeed(dl_buffer));
#endif
#ifdef WIND_INFO_RET
      float airspeed = stateGetAirspeed_f();
      DOWNLINK_SEND_WIND_INFO_RET(DefaultChannel, DefaultDevice, &wind.y, &wind.x, &airspeed);
#endif
    }
    break;
#endif /** WIND_INFO */

#ifdef HITL
    /** Infrared and GPS sensors are replaced by messages on the datalink */
    case DL_HITL_INFRARED: {
      /** This code simulates infrared.c:ir_update() */
      infrared.roll = DL_HITL_INFRARED_roll(dl_buffer);
      infrared.pitch = DL_HITL_INFRARED_pitch(dl_buffer);
      infrared.top = DL_HITL_INFRARED_top(dl_buffer);
    }
    break;

    case DL_HITL_UBX: {
      /** This code simulates gps_ubx.c:parse_ubx() */
      if (gps_msg_received) {
        gps_nb_ovrn++;
      } else {
        ubx_class = DL_HITL_UBX_class(dl_buffer);
        ubx_id = DL_HITL_UBX_id(dl_buffer);
        uint8_t l = DL_HITL_UBX_ubx_payload_length(dl_buffer);
        uint8_t *ubx_payload = DL_HITL_UBX_ubx_payload(dl_buffer);
        memcpy(ubx_msg_buf, ubx_payload, l);
        gps_msg_received = TRUE;
      }
    }
    break;
#endif /* HITL */

#ifdef DlSetting
    case DL_SETTING: {
      if (DL_SETTING_ac_id(dl_buffer) != AC_ID) { break; }
      uint8_t i = DL_SETTING_index(dl_buffer);
      float val = DL_SETTING_value(dl_buffer);
      DlSetting(i, val);
      DOWNLINK_SEND_DL_VALUE(DefaultChannel, DefaultDevice, &i, &val);
    }
    break;

    case DL_GET_SETTING: {
      if (DL_GET_SETTING_ac_id(dl_buffer) != AC_ID) { break; }
      uint8_t i = DL_GET_SETTING_index(dl_buffer);
      float val = settings_get_value(i);
      DOWNLINK_SEND_DL_VALUE(DefaultChannel, DefaultDevice, &i, &val);
    }
    break;
#endif /** Else there is no dl_settings section in the flight plan */

#if USE_JOYSTICK
    case DL_JOYSTICK_RAW: {
      if (DL_JOYSTICK_RAW_ac_id(dl_buffer) == AC_ID) {
        JoystickHandeDatalink(DL_JOYSTICK_RAW_roll(dl_buffer),
                              DL_JOYSTICK_RAW_pitch(dl_buffer),
                              DL_JOYSTICK_RAW_throttle(dl_buffer));
      }
    }
    break;
#endif // USE_JOYSTICK

#if defined RADIO_CONTROL && defined RADIO_CONTROL_TYPE_DATALINK
    case DL_RC_3CH: {
      //if (DL_RC_3CH_ac_id(dl_buffer) != TX_ID) { break; }
#ifdef RADIO_CONTROL_DATALINK_LED
      LED_TOGGLE(RADIO_CONTROL_DATALINK_LED);
#endif
      parse_rc_3ch_datalink(DL_RC_3CH_throttle_mode(dl_buffer),
                            DL_RC_3CH_roll(dl_buffer),
                            DL_RC_3CH_pitch(dl_buffer));
    }
    break;

    case DL_RC_4CH: {
      if (DL_RC_4CH_ac_id(dl_buffer) == AC_ID) {
#ifdef RADIO_CONTROL_DATALINK_LED
        LED_TOGGLE(RADIO_CONTROL_DATALINK_LED);
#endif
        parse_rc_4ch_datalink(DL_RC_4CH_mode(dl_buffer),
                              DL_RC_4CH_throttle(dl_buffer),
                              DL_RC_4CH_roll(dl_buffer),
                              DL_RC_4CH_pitch(dl_buffer),
                              DL_RC_4CH_yaw(dl_buffer));
      }
    }
    break;
#endif // RC_DATALINK

    default:
      break;
  }
