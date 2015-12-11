#ifdef LEGACY_PROTOCOL
if(clc.compat)
			Com_sprintf(name, sizeof(name), "demos/%s.%s%d", demoName, DEMOEXT, com_legacyprotocol->integer);
		else
#endif
			Com_sprintf(name, sizeof(name), "demos/%s.%s%d", demoName, DEMOEXT, com_protocol->integer);
