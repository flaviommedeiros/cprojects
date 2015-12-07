#ifdef CONFIG_SUN4
if (idprom->id_machtype == (SM_SUN4 | SM_4_260))
		sun4c_timers = &sun4_timer;
	else
#endif
	sun4c_timers = ioremap(SUN_TIMER_PHYSADDR,
	    sizeof(struct sun4c_timer_info));
