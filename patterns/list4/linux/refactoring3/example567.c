switch (nType) {
	case typeSingle:
	case typeDouble:
		{
			put_user(p[0], &pMem[2]);	/* single */
			put_user(p[1], &pMem[1]);	/* double msw */
			put_user(nType << 14, &pMem[0]);
		}
		break;

#ifdef CONFIG_FPE_NWFPE_XP
	case typeExtended:
		{
			put_user(p[2], &pMem[1]);	/* msw */
			put_user(p[1], &pMem[2]);
			put_user((p[0] & 0x80003fff) | (nType << 14), &pMem[0]);
		}
		break;
#endif
	}
