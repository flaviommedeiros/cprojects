int SSL_add_dir_cert_subjects_to_stack(STACK_OF(X509_NAME) *stack,
				       const char *dir)
	{
	OPENSSL_DIR_CTX *d = NULL;
	const char *filename;
	int ret = 0;

	CRYPTO_w_lock(CRYPTO_LOCK_READDIR);

	/* Note that a side effect is that the CAs will be sorted by name */

	while((filename = OPENSSL_DIR_read(&d, dir)))
		{
		char buf[1024];
		int r;

		if(strlen(dir)+strlen(filename)+2 > sizeof buf)
			{
			SSLerr(SSL_F_SSL_ADD_DIR_CERT_SUBJECTS_TO_STACK,SSL_R_PATH_TOO_LONG);
			goto err;
			}

#ifdef OPENSSL_SYS_VMS
		r = BIO_snprintf(buf,sizeof buf,"%s%s",dir,filename);
#else
		r = BIO_snprintf(buf,sizeof buf,"%s/%s",dir,filename);
#endif
		if (r <= 0 || r >= (int)sizeof(buf))
			goto err;
		if(!SSL_add_file_cert_subjects_to_stack(stack,buf))
			goto err;
		}

	if (errno)
		{
		SYSerr(SYS_F_OPENDIR, get_last_sys_error());
		ERR_add_error_data(3, "OPENSSL_DIR_read(&ctx, '", dir, "')");
		SSLerr(SSL_F_SSL_ADD_DIR_CERT_SUBJECTS_TO_STACK, ERR_R_SYS_LIB);
		goto err;
		}

	ret = 1;

err:
	if (d) OPENSSL_DIR_end(&d);
	CRYPTO_w_unlock(CRYPTO_LOCK_READDIR);
	return ret;
	}
