if (res == FR_OK		/* Not empty directory */
#if _FS_RPATH
                            || dclst == dj.fs->cdir	/* Current directory */
#endif
                           ) res = FR_DENIED;
