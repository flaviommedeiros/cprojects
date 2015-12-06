#ifdef USE_SCRYPT
if (kinterface == KL_SCRYPT)
		buffersize = SCRYPT_BUFFERSIZE;
	else
#endif
		buffersize = BUFFERSIZE;
