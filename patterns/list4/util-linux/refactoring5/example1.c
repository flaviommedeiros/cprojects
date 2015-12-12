#ifdef HAVE_WIDECHAR
if (fold_opt && MB_CUR_MAX > 1) {
				memset(mbc, '\0', MB_LEN_MAX);
				mbc_pos = 0;
				mbc[mbc_pos++] = c;
				state_bak = state;

				mblength = mbrtowc(&wc, mbc, mbc_pos, &state);
				/* The value of mblength is always less than 2 here. */
				switch (mblength) {
				case (size_t)-2:
					p--;
					file_pos_bak = Ftell(f) - 1;
					state = state_bak;
					use_mbc_buffer_flag = 1;
					break;

				case (size_t)-1:
					state = state_bak;
					column++;
					break;

				default:
					wc_width = wcwidth(wc);
					if (wc_width > 0)
						column += wc_width;
				}
			} else
#endif	/* HAVE_WIDECHAR */
			{
				if (isprint(c))
					column++;
			}
