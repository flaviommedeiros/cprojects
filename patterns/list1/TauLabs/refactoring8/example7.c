struct LibraryFunction PlatformLibrary_pathdesired[] =
{
#ifndef NO_FP
	{ PathDesired_Get,	"void PathDesiredGet(PathDesiredData *);" },
	{ PathDesired_Set,	"void PathDesiredSet(PathDesiredData *);" },
#endif
	{ NULL, NULL }
};
