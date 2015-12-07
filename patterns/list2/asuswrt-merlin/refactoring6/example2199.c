if (!strchr(str, '$')
	 && !strchr(str, '\\')
#if ENABLE_HUSH_TICK
	 && !strchr(str, '`')
#endif
	) {
		return NULL;
	}
