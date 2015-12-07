#ifdef BCMJTAG
if (BUSTYPE(sih->bustype) == JTAG_BUS) {
		uint32 *s, *d;
		uint sz = nvs;

		s = (uint32 *)(&nvh[1]);
		d = (uint32 *)new->vars;

		ASSERT(ISALIGNED((uintptr)s, sizeof(uint32)));
		ASSERT(ISALIGNED((uintptr)d, sizeof(uint32)));

		while (sz >= sizeof(uint32)) {
			*d++ = ltoh32(R_REG(osh, s++));
			sz -= sizeof(uint32);
		}
		if (sz) {
			union {
				uint32	w;
				char	b[sizeof(uint32)];
			} data;
			uint i;
			char *dst = (char *)d;

			data.w =  ltoh32(R_REG(osh, s));
			for (i = 0; i < sz; i++)
				*dst++ = data.b[i];
		}
	} else
#endif	/* BCMJTAG */
		bcopy((char *)(&nvh[1]), new->vars, nvs);
