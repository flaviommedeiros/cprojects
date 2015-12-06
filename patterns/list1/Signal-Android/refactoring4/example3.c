#ifdef OPENSSL_NO_CAMELLIA
if (((i++) % 5) == 0)
#else
			if (((i++) % 4) == 0)
#endif
				{
				BIO_printf(bio_err,"\n");
				nl=1;
				}
