# if BB_MMU
if (APPLET_IS_NOFORK(a))
# endif
		{
			return run_nofork_applet(a, argv);
		}
