switch (fpa11->fType[Fn]) {
	case typeSingle:
	case typeDouble:
		{
			get_user(p[0], &pMem[2]);	/* Single */
			get_user(p[1], &pMem[1]);	/* double msw */
			p[2] = 0;			/* empty */
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			get_user(p[1], &pMem[2]);
			get_user(p[2], &pMem[1]);	/* msw */
			p[0] = (x & 0x80003fff);
		}
		break;
#endif
	}
