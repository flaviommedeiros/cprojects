#ifdef HAVE_XKB
if (event->type == display->xkb_base_event_type)
    {
      meta_topic (META_DEBUG_KEYBINDINGS,
                  "XKB mapping changed, will redo keybindings\n");

      keymap_changed = TRUE;
      modmap_changed = TRUE;
    }
  else
#endif
  if (event->xmapping.request == MappingModifier)
    {
      meta_topic (META_DEBUG_KEYBINDINGS,
                  "Received MappingModifier event, will reload modmap and redo keybindings\n");

      modmap_changed = TRUE;
    }
  else if (event->xmapping.request == MappingKeyboard)
    {
      meta_topic (META_DEBUG_KEYBINDINGS,
                  "Received MappingKeyboard event, will reload keycodes and redo keybindings\n");

      keymap_changed = TRUE;
    }
