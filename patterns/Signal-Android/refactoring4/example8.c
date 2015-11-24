#ifndef OPENSSL_SYS_VMS
if (access(outdir,R_OK|W_OK|X_OK) != 0)
#else
		if (_access(outdir,R_OK|W_OK|X_OK) != 0)
#endif
			{
			BIO_printf(bio_err,"I am unable to access the %s directory\n",outdir);
			perror(outdir);
			goto err;
			}
