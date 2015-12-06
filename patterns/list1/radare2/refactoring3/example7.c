switch (type) {
#ifdef QUICK
	case 2:
		p--;
		(void)munmap ((void *)p, sizeof(*p) * (entries + 1));
		break;
#endif
	case 1:
		p--;
		/*FALLTHROUGH*/
	case 0:
		free (p);
		p = NULL;
		break;
	default:
		abort ();
	}
