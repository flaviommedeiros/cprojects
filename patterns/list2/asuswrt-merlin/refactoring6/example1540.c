if (((b->type == bp_breakpoint) || (b->type == bp_hardware_breakpoint))
	&& breakpoint_enabled (b) && !b->loc->duplicate
#ifdef PC_SOLIB
	&& PC_SOLIB (b->loc->address)
#else
	&& solib_address (b->loc->address)
#endif
	)
	b->enable_state = bp_shlib_disabled;
