if (
#if !ENABLE_EXTRA_COMPAT
					regexec(&gl->compiled_regex, line, 1, &gl->matched_range, 0) == 0
#else
					re_search(&gl->compiled_regex, line, line_len,
							/*start:*/ 0, /*range:*/ line_len,
							&gl->matched_range) >= 0
#endif
				) {
					if (option_mask32 & OPT_x) {
						found = (gl->matched_range.rm_so == 0
						         && line[gl->matched_range.rm_eo] == '\0');
					} else if (!(option_mask32 & OPT_w)) {
						found = 1;
					} else {
						char c = ' ';
						if (gl->matched_range.rm_so)
							c = line[gl->matched_range.rm_so - 1];
						if (!isalnum(c) && c != '_') {
							c = line[gl->matched_range.rm_eo];
							if (!c || (!isalnum(c) && c != '_'))
								found = 1;
						}
					}
				}
