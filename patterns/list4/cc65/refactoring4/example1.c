#ifdef NO_FUNCS_TAKE_STRUCTS
if (ptinrect(&x, &screen) == 0)
#else
                if (ptinrect(x, screen) == 0)
#endif
		{
                        printf("not ");
		}
