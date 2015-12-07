#ifdef CONFIG_SUN4
if (idprom->id_machtype == (SM_SUN4 | SM_4_260)) 
	  clear_intr = sun4_timer.timer_limit10;
	else
#endif
	clear_intr = sun4c_timers->timer_limit10;
