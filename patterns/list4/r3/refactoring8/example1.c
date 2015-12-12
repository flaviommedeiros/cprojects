REBDEV *Devices[RDI_LIMIT] =
{
	0,
	&Dev_StdIO,
	0,
	&Dev_File,
	&Dev_Event,
	&Dev_Net,
	&Dev_DNS,
#ifndef MIN_OS
	&Dev_Clipboard,
#endif
	0,
};
