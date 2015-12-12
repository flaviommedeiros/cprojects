#ifdef HAVE_XKB
if (display->xkb_base_event_type > 0)
    {
      unsigned int primary_modifier;
      XkbStateRec state;

      primary_modifier = get_primary_modifier (display, display->grab_mask);

      XkbGetState (display->xdisplay, XkbUseCoreKbd, &state);

      if (!(primary_modifier & state.mods))
	return TRUE;
    }
  else
#endif
    {
      if (keycode_is_primary_modifier (display, keycode, display->grab_mask))
	return TRUE;
    }
