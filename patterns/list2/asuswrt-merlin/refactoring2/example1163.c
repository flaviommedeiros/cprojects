#if XFS_BIG_INUMS
if (mp->m_maxicount)
#if XFS_BIG_INUMS
		if (!mp->m_inoadd)
#endif
			statp->f_files = min_t(typeof(statp->f_files),
						statp->f_files,
						mp->m_maxicount);
