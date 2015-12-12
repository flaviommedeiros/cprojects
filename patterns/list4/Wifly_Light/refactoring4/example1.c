#if !_FS_READONLY
if (ofs > fp->fsize && !(fp->flag & FA_WRITE))
#else
	if (ofs > fp->fsize)
#endif
		ofs = fp->fsize;
