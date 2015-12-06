#ifndef DEDICATED
if (!libHandle)
#endif
		{
			libHandle = Sys_TryLibraryLoad(basepath, DEFAULT_MODGAME, fname);
		}
