if (res == FR_OK		/* Not empty dir */
#if _FS_RPATH
						|| dclst == dj.fs->cdir	/* Current dir */
#endif
						) res = FR_DENIED;
