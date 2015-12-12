#if 1
if (!(b & ~31))
#else
		if (b == 0)
#endif
		{
			/* End of row */
			IT_SET_END_ROW(entry);
			entry++;
			continue;
		}
