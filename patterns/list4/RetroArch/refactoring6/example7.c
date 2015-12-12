if (*state_p1 & (GX_WIIMOTE_HOME
#ifdef HW_RVL
            | GX_CLASSIC_HOME
#endif
            ))
      *lifecycle_state |= (1ULL << RARCH_MENU_TOGGLE);
