#ifndef __MSDOS__
if (_rl_term_clreol)
    tputs (_rl_term_clreol, 1, _rl_output_character_function);
  else
#endif
  if (count)
    space_to_eol (count);
