#ifdef HAVE_WIDECHAR
if (MB_CUR_MAX > 1) {
					wchar_t wc;
					size_t pos = 0, mblength;
					mbstate_t state, state_bak;

					memset(&state, '\0', sizeof(mbstate_t));

					while (1) {
						state_bak = state;
						mblength =
						    mbrtowc(&wc, buf + pos,
							    sp - buf, &state);

						state = (mblength == (size_t)-2
							 || mblength ==
							 (size_t)-1) ? state_bak
						    : state;
						mblength =
						    (mblength == (size_t)-2
						     || mblength == (size_t)-1
						     || mblength ==
						     0) ? 1 : mblength;

						if (buf + pos + mblength >= sp)
							break;

						pos += mblength;
					}

					if (mblength == 1) {
						ERASEONECOLUMN(docrterase);
					} else {
						int wc_width;
						wc_width = wcwidth(wc);
						wc_width =
						    (wc_width <
						     1) ? 1 : wc_width;
						while (wc_width--) {
							ERASEONECOLUMN(docrterase);
						}
					}

					while (mblength--) {
						--promptlen;
						--sp;
					}
				} else
#endif	/* HAVE_WIDECHAR */
				{
					--promptlen;
					ERASEONECOLUMN(docrterase);
					--sp;
				}
