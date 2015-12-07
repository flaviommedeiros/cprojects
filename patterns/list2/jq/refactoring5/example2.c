#ifdef Honor_FLT_ROUNDS
if (bc->rounding != 1) {
		if (i > 0)
			b = lshift(C, b, i);
		if (dsign)
			b = increment(b);
		}
	else
#endif
		{
		b = lshift(C, b, ++i);
		b->x[0] |= 1;
		}
