IoMethodTable methodTable[] = {
#ifdef WIN32
	{"shellExecute", IoObject_shellExecute},
	{"installPrefix", IoObject_installPrefix},
#else
	{"daemon", IoObject_daemon},
#endif
	{"errorNumber", IoObject_errorNumberDescription},
	{"exit", IoObject_exit},
	{"getEnvironmentVariable", IoObject_getEnvironmentVariable},
	{"setEnvironmentVariable", IoObject_setEnvironmentVariable},
	{"system", IoObject_system},
	//{"memorySizeOfState", IoObject_memorySizeOfState},
	//{"compactState", IoObject_compactState},
	{"platform", IoObject_platform},
	{"platformVersion", IoObject_platformVersion},
	{"sleep", IoObject_sleep},
	{"activeCpus", IoObject_activeCpus},
	{"recycledObjectCount", IoObject_recycledObjectCount},
	{"maxRecycledObjects", IoObject_maxRecycledObjects},
	{"setMaxRecycledObjects", IoObject_setMaxRecycledObjects},
	{"symbols", IoObject_symbols},
	{"setLobby", IoObject_setLobby},
	{"thisProcessPid", IoObject_thisProcessPid},
	{NULL, NULL},
	};
