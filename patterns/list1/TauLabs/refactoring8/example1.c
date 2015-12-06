struct LibraryFunction PlatformLibrary_accels[] =
{
#ifndef NO_FP
	{ Accels_Get,	"void AccelsGet(AccelsData *);" },
#endif
	{ NULL, NULL }
};
