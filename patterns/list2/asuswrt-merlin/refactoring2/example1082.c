#ifndef USE_INODE_IO
if (ext_journal)
#endif
		retval = io_ptr->open(journal_name, IO_FLAG_RW,
				      &ctx->journal_io);
