#ifndef __MSDOS__
if (_rl_term_backspace)
    for (i = 0; i < count; i++)
      tputs (_rl_term_backspace, 1, _rl_output_character_function);
  else
#endif
    for (i = 0; i < count; i++)
      putc ('\b', _rl_out_stream);
