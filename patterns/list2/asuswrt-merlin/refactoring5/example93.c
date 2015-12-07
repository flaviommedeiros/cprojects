#ifdef RTN56U
if (nvram_match(strcat_r(prefix, "country_code", tmp), "TW"))
						sprintf(tmpstr,"%d;%d",56,165);
					else
#endif
					sprintf(tmpstr,"%d",165);
