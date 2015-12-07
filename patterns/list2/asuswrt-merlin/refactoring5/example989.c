#ifdef CONFIG_64BIT
if (!in_compat_space_p(addr)) {
		i_lui(buf, rs, rel_highest(addr));
		if (rel_higher(addr))
			i_daddiu(buf, rs, rs, rel_higher(addr));
		if (rel_hi(addr)) {
			i_dsll(buf, rs, rs, 16);
			i_daddiu(buf, rs, rs, rel_hi(addr));
			i_dsll(buf, rs, rs, 16);
		} else
			i_dsll32(buf, rs, rs, 0);
	} else
#endif
		i_lui(buf, rs, rel_hi(addr));
