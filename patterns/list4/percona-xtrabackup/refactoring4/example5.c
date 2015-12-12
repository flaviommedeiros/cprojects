#if HAVE_FSEEKO
if (fseeko(mine->f, request, SEEK_CUR) != 0)
#else
	if (fseek(mine->f, request, SEEK_CUR) != 0)
#endif
	{
		mine->can_skip = 0;
		return (0);
	}
