#ifdef TERMINAL_EMULATION_USES_CURSES
if (!d->emulate_terminal)
    {
      current_attrs = d->terminal_attrs;
      d->terminal_attrs = attrs;
    }
  else

#endif

    {
      current_attrs = d->current.attrs;
      d->current.attrs = attrs;
    }
