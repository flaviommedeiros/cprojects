if(demo_protocols[i] || protocol == com_protocol->integer
#ifdef LEGACY_PROTOCOL
		   || protocol == com_legacyprotocol->integer
#endif
		  )
		{
			Com_sprintf(name, sizeof(name), "demos/%s", arg);
			FS_FOpenFileRead(name, &clc.demofile, qtrue);
		}
		else
		{
			int len;

			Com_Printf("Protocol %d not supported for demos\n", protocol);
			len = ext_test - arg;

			if(len >= ARRAY_LEN(retry))
				len = ARRAY_LEN(retry) - 1;

			Q_strncpyz(retry, arg, len + 1);
			retry[len] = '\0';
			protocol = CL_WalkDemoExt(retry, name, &clc.demofile);
		}
