#ifdef DEBUG_X6500_SET_REGISTER
if (x6500_get_register(jp, addr) != nv)
#else
	if (0)
#endif
	{
		applog(LOG_WARNING, "x6500_set_register failed %x=%08x", addr, nv);
		goto retry;
	}
