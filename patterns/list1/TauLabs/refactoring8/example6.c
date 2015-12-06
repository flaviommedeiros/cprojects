struct LibraryFunction PlatformLibrary_magnetometer[] =
{
#ifndef NO_FP
	{ Magnetometer_Get,	"void MagnetometerGet(MagnetometerData *);" },
#endif
	{ NULL, NULL }
};
