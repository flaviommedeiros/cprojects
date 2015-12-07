#ifdef RTCONFIG_DSL
if(wan_type == WANS_DUALWAN_IF_DSL)
#endif
		if (nvram_match("dsl0_proto", "ipoa"))
		{
			stop_ipoa();
		}
