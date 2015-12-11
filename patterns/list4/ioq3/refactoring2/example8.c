#ifdef ALTERNATE_CURL_LIB
if(!(cURLLib = Sys_LoadDll(ALTERNATE_CURL_LIB, qtrue)))
#endif
			return qfalse;
