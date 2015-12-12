#ifdef HAVE_LOCALE_T
if (mylocale)
			{
				if (wasalnum)
					workspace[curr_char] = towlower_l(workspace[curr_char], mylocale);
				else
					workspace[curr_char] = towupper_l(workspace[curr_char], mylocale);
				wasalnum = iswalnum_l(workspace[curr_char], mylocale);
			}
			else
#endif
			{
				if (wasalnum)
					workspace[curr_char] = towlower(workspace[curr_char]);
				else
					workspace[curr_char] = towupper(workspace[curr_char]);
				wasalnum = iswalnum(workspace[curr_char]);
			}
