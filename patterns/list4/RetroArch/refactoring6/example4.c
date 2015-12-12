if (
#ifdef HW_RVL
         ((*state_p1 & GX_CLASSIC_RSTICK_RIGHT) && (*state_p1 & GX_CLASSIC_ZR_TRIGGER)) ||
#endif
         ((*state_p1 & GX_GC_RSTICK_RIGHT) && (*state_p1 & GX_GC_Z_TRIGGER))
      )
      *lifecycle_state |= (1ULL << RARCH_STATE_SLOT_PLUS);
