#ifdef HAVE_LOCALE_T
if (mylocale)
				workspace[curr_char] = towupper_l(workspace[curr_char], mylocale);
			else
#endif
				workspace[curr_char] = towupper(workspace[curr_char]);
