struct LibraryFunction PlatformLibrary_baroaltitude[] =
{
#ifndef NO_FP
	{ BaroAltitude_Get,	"void BaroAltitudeGet(BaroAltitudeData *);" },
#endif
	{ NULL, NULL }
};
