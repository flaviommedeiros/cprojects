if ((e = lineeditor_input_decoder_init
             (&d->input_decoder,
#ifdef USE_WIN32
              0,
#else
              1,
#endif
              emacs_bindings,
              terminal_type == NULL))
      != ___FIX(___NO_ERR))
    return e;
