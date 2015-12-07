#ifdef CONFIG_DUMMY_CONSOLE
if (conswitchp == &dummy_con)
		take_over_console(&prom_con, 0, MAX_NR_CONSOLES-1, 1);
	else
#endif
	if (conswitchp == &prom_con)
		promcon_init_unimap(vc_cons[fg_console].d);
