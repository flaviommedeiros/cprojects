#ifdef FIQ_VSYNC
if (idx == 'p') {
			fiq_bridge_pulse_trigger(&fiq_handle_item);
	}
	else
#endif
	{
		up(&di_sema);
	}
