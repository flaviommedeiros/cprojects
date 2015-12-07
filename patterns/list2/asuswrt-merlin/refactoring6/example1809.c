if (xbsd_initlabel(
#if defined(__alpha__) || defined(__powerpc__) || defined(__hppa__) || \
	defined(__s390__) || defined(__s390x__)
				NULL
#else
				xbsd_part
#endif
			) == 1) {
				xbsd_print_disklabel(1);
				return 1;
			}
