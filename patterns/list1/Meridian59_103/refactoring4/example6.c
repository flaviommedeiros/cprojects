#if defined(_WIN32) || defined(__CYGWIN__)
if (u16[0] == 0 && (u16[1] == '/' || u16[1] == '\\'))
#else
			if (u16[0] == 0 && u16[1] == '/')
#endif
			{
				ulast = u16 + 2;
				ulen_last = u16len -1;
			}
