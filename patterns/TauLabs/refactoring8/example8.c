struct LibraryFunction PlatformLibrary_pathstatus[] =
{
#ifndef NO_FP
	{ PathStatus_Get,	"void PathStatusGet(PathStatusData *);" },
#endif
	{ NULL, NULL }
};
