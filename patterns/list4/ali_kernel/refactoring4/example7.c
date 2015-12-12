#ifdef CMX_CONF_DEBUG
if (conf->software && members > 1)
#else
			if (conf->software && members > 2)
#endif
				mustmix = 1;
