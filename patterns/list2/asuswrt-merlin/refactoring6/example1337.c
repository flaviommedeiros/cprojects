if (
#ifdef DROPBEAR_RSA
			key->type == DROPBEAR_SIGNKEY_RSA ||
#endif
#ifdef DROPBEAR_DSS
			key->type == DROPBEAR_SIGNKEY_DSS ||
#endif
			0)
	{
		/*
		 * Fetch the key blobs.
		 */
		keyblob = buf_new(3000);
		buf_put_priv_key(keyblob, key, key->type);

		buf_setpos(keyblob, 0);
		/* skip the "ssh-rsa" or "ssh-dss" header */
		buf_incrpos(keyblob, buf_getint(keyblob));

		/*
		 * Find the sequence of integers to be encoded into the OpenSSH
		 * key blob, and also decide on the header line.
		 */
		numbers[0].start = zero; numbers[0].bytes = 1; zero[0] = '\0';

	#ifdef DROPBEAR_RSA
		if (key->type == DROPBEAR_SIGNKEY_RSA) {

			if (key->rsakey->p == NULL || key->rsakey->q == NULL) {
				fprintf(stderr, "Pre-0.33 Dropbear keys cannot be converted to OpenSSH keys.\n");
				goto error;
			}

			/* e */
			numbers[2].bytes = buf_getint(keyblob);
			numbers[2].start = buf_getptr(keyblob, numbers[2].bytes);
			buf_incrpos(keyblob, numbers[2].bytes);
			
			/* n */
			numbers[1].bytes = buf_getint(keyblob);
			numbers[1].start = buf_getptr(keyblob, numbers[1].bytes);
			buf_incrpos(keyblob, numbers[1].bytes);
			
			/* d */
			numbers[3].bytes = buf_getint(keyblob);
			numbers[3].start = buf_getptr(keyblob, numbers[3].bytes);
			buf_incrpos(keyblob, numbers[3].bytes);
			
			/* p */
			numbers[4].bytes = buf_getint(keyblob);
			numbers[4].start = buf_getptr(keyblob, numbers[4].bytes);
			buf_incrpos(keyblob, numbers[4].bytes);
			
			/* q */
			numbers[5].bytes = buf_getint(keyblob);
			numbers[5].start = buf_getptr(keyblob, numbers[5].bytes);
			buf_incrpos(keyblob, numbers[5].bytes);

			/* now calculate some extra parameters: */
			m_mp_init(&tmpval);
			m_mp_init(&dmp1);
			m_mp_init(&dmq1);
			m_mp_init(&iqmp);

			/* dmp1 = d mod (p-1) */
			if (mp_sub_d(key->rsakey->p, 1, &tmpval) != MP_OKAY) {
				fprintf(stderr, "Bignum error for p-1\n");
				goto error;
			}
			if (mp_mod(key->rsakey->d, &tmpval, &dmp1) != MP_OKAY) {
				fprintf(stderr, "Bignum error for dmp1\n");
				goto error;
			}

			/* dmq1 = d mod (q-1) */
			if (mp_sub_d(key->rsakey->q, 1, &tmpval) != MP_OKAY) {
				fprintf(stderr, "Bignum error for q-1\n");
				goto error;
			}
			if (mp_mod(key->rsakey->d, &tmpval, &dmq1) != MP_OKAY) {
				fprintf(stderr, "Bignum error for dmq1\n");
				goto error;
			}

			/* iqmp = (q^-1) mod p */
			if (mp_invmod(key->rsakey->q, key->rsakey->p, &iqmp) != MP_OKAY) {
				fprintf(stderr, "Bignum error for iqmp\n");
				goto error;
			}

			extrablob = buf_new(2000);
			buf_putmpint(extrablob, &dmp1);
			buf_putmpint(extrablob, &dmq1);
			buf_putmpint(extrablob, &iqmp);
			buf_setpos(extrablob, 0);
			mp_clear(&dmp1);
			mp_clear(&dmq1);
			mp_clear(&iqmp);
			mp_clear(&tmpval);
			
			/* dmp1 */
			numbers[6].bytes = buf_getint(extrablob);
			numbers[6].start = buf_getptr(extrablob, numbers[6].bytes);
			buf_incrpos(extrablob, numbers[6].bytes);
			
			/* dmq1 */
			numbers[7].bytes = buf_getint(extrablob);
			numbers[7].start = buf_getptr(extrablob, numbers[7].bytes);
			buf_incrpos(extrablob, numbers[7].bytes);
			
			/* iqmp */
			numbers[8].bytes = buf_getint(extrablob);
			numbers[8].start = buf_getptr(extrablob, numbers[8].bytes);
			buf_incrpos(extrablob, numbers[8].bytes);

			nnumbers = 9;
			header = "-----BEGIN RSA PRIVATE KEY-----\n";
			footer = "-----END RSA PRIVATE KEY-----\n";
		}
	#endif /* DROPBEAR_RSA */

	#ifdef DROPBEAR_DSS
		if (key->type == DROPBEAR_SIGNKEY_DSS) {

			/* p */
			numbers[1].bytes = buf_getint(keyblob);
			numbers[1].start = buf_getptr(keyblob, numbers[1].bytes);
			buf_incrpos(keyblob, numbers[1].bytes);

			/* q */
			numbers[2].bytes = buf_getint(keyblob);
			numbers[2].start = buf_getptr(keyblob, numbers[2].bytes);
			buf_incrpos(keyblob, numbers[2].bytes);

			/* g */
			numbers[3].bytes = buf_getint(keyblob);
			numbers[3].start = buf_getptr(keyblob, numbers[3].bytes);
			buf_incrpos(keyblob, numbers[3].bytes);

			/* y */
			numbers[4].bytes = buf_getint(keyblob);
			numbers[4].start = buf_getptr(keyblob, numbers[4].bytes);
			buf_incrpos(keyblob, numbers[4].bytes);

			/* x */
			numbers[5].bytes = buf_getint(keyblob);
			numbers[5].start = buf_getptr(keyblob, numbers[5].bytes);
			buf_incrpos(keyblob, numbers[5].bytes);

			nnumbers = 6;
			header = "-----BEGIN DSA PRIVATE KEY-----\n";
			footer = "-----END DSA PRIVATE KEY-----\n";
		}
	#endif /* DROPBEAR_DSS */

		/*
		 * Now count up the total size of the ASN.1 encoded integers,
		 * so as to determine the length of the containing SEQUENCE.
		 */
		len = 0;
		for (i = 0; i < nnumbers; i++) {
			len += ber_write_id_len(NULL, 2, numbers[i].bytes, 0);
			len += numbers[i].bytes;
		}
		seqlen = len;
		/* Now add on the SEQUENCE header. */
		len += ber_write_id_len(NULL, 16, seqlen, ASN1_CONSTRUCTED);
		/* Round up to the cipher block size, ensuring we have at least one
		 * byte of padding (see below). */
		outlen = len;
		if (passphrase)
			outlen = (outlen+8) &~ 7;

		/*
		 * Now we know how big outblob needs to be. Allocate it.
		 */
		outblob = (unsigned char*)m_malloc(outlen);

		/*
		 * And write the data into it.
		 */
		pos = 0;
		pos += ber_write_id_len(outblob+pos, 16, seqlen, ASN1_CONSTRUCTED);
		for (i = 0; i < nnumbers; i++) {
			pos += ber_write_id_len(outblob+pos, 2, numbers[i].bytes, 0);
			memcpy(outblob+pos, numbers[i].start, numbers[i].bytes);
			pos += numbers[i].bytes;
		}
	}
