if (strcmp(e->d_name+len,
#if defined(__CYGWIN__)
				   ".dll"
#else
				   ".so"
#endif
				    ))
				continue;
