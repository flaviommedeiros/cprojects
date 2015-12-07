#ifdef _DIRENT_HAVE_D_TYPE
if (dent->d_type != DT_SOCK && dent->d_type != DT_UNKNOWN)
			continue;
