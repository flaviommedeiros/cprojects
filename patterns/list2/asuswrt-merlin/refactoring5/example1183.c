#ifdef RTCONFIG_TCODE
if (!nvram_contains_word("rc_support", "yadns") &&
	    !nvram_contains_word("rc_support", "yadns_hideqis"))
#endif
	{
		/* 0: disable, 1: full, -1: partial without qis */
		int yadns_support;

		switch (model) {
		case MODEL_RTN11P:
		case MODEL_RTN300:
			yadns_support = nvram_match("reg_spec", "CE") && nvram_match("wl_reg_2g", "2G_CH13");	//for CE & RU area. (but IN could also be included)
			break;
#ifdef RTCONFIG_TCODE
		case MODEL_RTN12D1:
		case MODEL_RTN12HP_B1:
		case MODEL_RTAC51U:
			/* Only enabled by territory_code */
			yadns_support = 0;
			break;
#endif
		default:
			/* Enabled by default since YANDEXDNS=y */
			yadns_support = 1;
		}
		if (yadns_support == 0)
			nvram_set_int("yadns_enable_x", 0);
		else if (yadns_support < 0)
			add_rc_support("yadns_hideqis");
		else
			add_rc_support("yadns");
	}
