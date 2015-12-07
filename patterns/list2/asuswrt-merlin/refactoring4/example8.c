#if defined (HANDLE_MULTIBYTE)
if (_rl_is_mbchar_matched (rl_line_buffer, pos, rl_end, smbchar, len))
#else
	  if (rl_line_buffer[pos] == schar)
#endif
	    {
	      count--;
	      if (dir < 0)
	        rl_point = (dir == BTO) ? _rl_find_next_mbchar (rl_line_buffer, pos, 1, MB_FIND_ANY)
					: pos;
	      else
		rl_point = (dir == FTO) ? _rl_find_prev_mbchar (rl_line_buffer, pos, MB_FIND_ANY)
					: pos;
	      break;
	    }
