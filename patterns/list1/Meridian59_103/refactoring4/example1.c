#if HAVE_FSEEKO
if (fseeko(mine->f, skip, SEEK_CUR) != 0)
#elif HAVE__FSEEKI64
	if (_fseeki64(mine->f, skip, SEEK_CUR) != 0)
#else
	if (fseek(mine->f, skip, SEEK_CUR) != 0)
#endif
	{
		mine->can_skip = 0;
		return (0);
	}
