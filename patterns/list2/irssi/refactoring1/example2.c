if (cmd == LINE_COLOR_EXT || cmd == LINE_COLOR_EXT_BG)
				ptr++;
#ifdef TERM_TRUECOLOR
			else if (cmd == LINE_COLOR_24)
				ptr+=4;
#endif
