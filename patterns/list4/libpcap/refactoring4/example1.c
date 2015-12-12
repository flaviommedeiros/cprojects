#if defined(KERNEL) || defined(_KERNEL)
if (from + p->k < from || from + p->k >= len)
#else
				if (from + p->k >= len)
#endif
					return 0;
