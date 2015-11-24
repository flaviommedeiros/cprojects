if (*state_p1 & ((UINT64_C(1) << GX_GC_HOME)
#ifdef HW_RVL
            | (UINT64_C(1) << GX_WIIMOTE_HOME)
            | (UINT64_C(1) << GX_CLASSIC_HOME)
#ifdef HAVE_LIBSICKSAXIS
            | (UINT64_C(1) << GX_SIXAXIS_PS)
#endif
#endif
            ))
    
   BIT64_SET(lifecycle_state, RARCH_MENU_TOGGLE);
