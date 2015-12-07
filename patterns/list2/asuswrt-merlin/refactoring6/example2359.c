if ((config0 & CONF_BE) != 
#ifdef CONFIG_CPU_LITTLE_ENDIAN
	    0
#else
	    CONF_BE
#endif
	) {
		panic("Kernel compiled little-endian, but running on a big-endian cpu");
	}
