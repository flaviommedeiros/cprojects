#ifdef WANT_LEAD_0
if (f__scale <= 0 && delta > 0) {
		delta--;
		insert0 = 1;
		}
	else
#endif
	if (delta < 0) {
nogood:
		while(--w >= 0)
			PUT('*');
		return(0);
		}
