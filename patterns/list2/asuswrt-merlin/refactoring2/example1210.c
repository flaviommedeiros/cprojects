#ifndef NO_DETECT_INTERNET
if(strcmp(dualwan_mode, "lb"))
#endif
				nvram_set_int("link_internet", 1);
