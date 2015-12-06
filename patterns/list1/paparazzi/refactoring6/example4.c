if ((autopilot_mode != AP_MODE_HOME)
#if UNLOCKED_HOME_MODE
               /* Allowed to leave home mode when UNLOCKED_HOME_MODE */
               || !too_far_from_home
#endif
              ) {
        autopilot_set_mode(new_autopilot_mode);
      }
