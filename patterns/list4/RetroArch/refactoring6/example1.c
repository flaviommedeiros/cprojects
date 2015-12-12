if (
#ifdef HW_RVL
         ((*state_p1 & GX_CLASSIC_RSTICK_DOWN) && !(*state_p1 & GX_CLASSIC_ZR_TRIGGER)) ||
#endif
         ((*state_p1 & GX_GC_RSTICK_DOWN) && !(*state_p1 & GX_GC_Z_TRIGGER))
      )
      *lifecycle_state |= (1ULL << RARCH_FAST_FORWARD_HOLD_KEY);
