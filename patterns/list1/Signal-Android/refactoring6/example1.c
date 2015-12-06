if (rename(serialfile,buf[1]) < 0 && errno != ENOENT
#ifdef ENOTDIR
			&& errno != ENOTDIR
#endif
	   )		{
			BIO_printf(bio_err,
				"unable to rename %s to %s\n",
				serialfile, buf[1]);
			perror("reason");
			goto err;
			}
