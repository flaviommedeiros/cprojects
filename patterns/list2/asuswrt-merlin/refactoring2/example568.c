#if 0
if (ext_journal)
#endif
	{
		int flags = IO_FLAG_RW;
		if (!(ctx->mount_flags & EXT2_MF_ISROOT &&
		      ctx->mount_flags & EXT2_MF_READONLY))
			flags |= IO_FLAG_EXCLUSIVE;
		if ((ctx->mount_flags & EXT2_MF_READONLY) &&
		    (ctx->options & E2F_OPT_FORCE))
			flags &= ~IO_FLAG_EXCLUSIVE;


		retval = io_ptr->open(journal_name, flags,
				      &ctx->journal_io);
	}
