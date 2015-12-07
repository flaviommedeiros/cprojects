#ifdef RTCONFIG_BWDPI
if(nvram_get_int("qos_type") == 1){
					stop_dpi_engine_service(1);
				}
				else
#endif
				stop_iQos();
