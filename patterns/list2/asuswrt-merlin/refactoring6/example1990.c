if ((strcmp(wan_proto, "dhcp") && strcmp(wan_proto, "static"))
#ifdef RTCONFIG_BWDPI
		|| check_bwdpi_nvram_setting()
#endif
		) {
			nvram_set_int("ctf_fa_mode", CTF_FA_DISABLED);
			_dprintf("wan_proto:%s not support FA mode...\n", wan_proto);
		}
