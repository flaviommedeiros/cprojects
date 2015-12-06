if ((stateGetPositionUtm_f()->alt > bungee_point.z + BUNGEE_TAKEOFF_HEIGHT)
#if USE_AIRSPEED
          && (stateGetAirspeed_f() > BUNGEE_TAKEOFF_AIRSPEED)
#endif
          ) {
        CTakeoffStatus = Finished;
        return FALSE;
      } else {
        return TRUE;
      }
