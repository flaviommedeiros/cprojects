#ifdef HAVE_LOCALE_T
if (mylocale)
				workspace[curr_char] = towlower_l(workspace[curr_char], mylocale);
			else
#endif
				workspace[curr_char] = towlower(workspace[curr_char]);
