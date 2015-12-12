#ifdef WANT_LEAD_0
if (buf[0] == '0' && --n == w)
			++b;
		else
#endif
		{
			while(--w >= 0)
				PUT('*');
			return 0;
			}
