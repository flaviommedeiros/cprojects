#ifdef NO_64BIT_MATH
if (low32(key->num_left) == 0 && high32(key->num_left == 0))
#else
  if (key->num_left < 1)
#endif
  { /* we just hit the hard limit */
    key->state = key_state_expired;
    return key_event_hard_limit;
  }
