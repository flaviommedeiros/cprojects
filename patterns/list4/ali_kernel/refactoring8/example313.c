static const char *space_names[] = {
	[0]		= "Space 0",
	[USER_DATA]	= "User Data",
	[USER_PROGRAM]	= "User Program",
#ifndef CONFIG_SUN3
	[3]		= "Space 3",
#else
	[FC_CONTROL]	= "Control",
#endif
	[4]		= "Space 4",
	[SUPER_DATA]	= "Super Data",
	[SUPER_PROGRAM]	= "Super Program",
	[CPU_SPACE]	= "CPU"
};
