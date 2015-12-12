#if !defined(_WIN32) && !defined(__CYGWIN__)
if (mode & 0111)
#endif
					/* set all exec bit ON */
					mode |= 0111;
