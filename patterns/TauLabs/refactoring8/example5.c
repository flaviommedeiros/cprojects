struct LibraryFunction PlatformLibrary_gyros[] =
{
#ifndef NO_FP
	{ Gyros_Get,	"void GyrosGet(GyrosData *);" },
#endif
	{ NULL, NULL }
};
