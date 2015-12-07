#if defined (VI_MODE)
if (rl_end <= point && rl_editing_mode == vi_mode)
	point = _rl_find_prev_mbchar (rl_line_buffer, rl_end, MB_FIND_NONZERO);
