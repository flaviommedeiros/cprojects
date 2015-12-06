int PKCS7_verify(PKCS7 *p7, STACK_OF(X509) *certs, X509_STORE *store,
					BIO *indata, BIO *out, int flags)
{
	STACK_OF(X509) *signers;
	X509 *signer;
	STACK_OF(PKCS7_SIGNER_INFO) *sinfos;
	PKCS7_SIGNER_INFO *si;
	X509_STORE_CTX cert_ctx;
	char buf[4096];
	int i, j=0, k, ret = 0;
	BIO *p7bio;
	BIO *tmpin, *tmpout;

	if(!p7) {
		PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_INVALID_NULL_POINTER);
		return 0;
	}

	if(!PKCS7_type_is_signed(p7)) {
		PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_WRONG_CONTENT_TYPE);
		return 0;
	}

	/* Check for no data and no content: no data to verify signature */
	if(PKCS7_get_detached(p7) && !indata) {
		PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_NO_CONTENT);
		return 0;
	}
#if 0
	/* NB: this test commented out because some versions of Netscape
	 * illegally include zero length content when signing data.
	 */

	/* Check for data and content: two sets of data */
	if(!PKCS7_get_detached(p7) && indata) {
				PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_CONTENT_AND_DATA_PRESENT);
		return 0;
	}
#endif

	sinfos = PKCS7_get_signer_info(p7);

	if(!sinfos || !sk_PKCS7_SIGNER_INFO_num(sinfos)) {
		PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_NO_SIGNATURES_ON_DATA);
		return 0;
	}


	signers = PKCS7_get0_signers(p7, certs, flags);

	if(!signers) return 0;

	/* Now verify the certificates */

	if (!(flags & PKCS7_NOVERIFY)) for (k = 0; k < sk_X509_num(signers); k++) {
		signer = sk_X509_value (signers, k);
		if (!(flags & PKCS7_NOCHAIN)) {
			if(!X509_STORE_CTX_init(&cert_ctx, store, signer,
							p7->d.sign->cert))
				{
				PKCS7err(PKCS7_F_PKCS7_VERIFY,ERR_R_X509_LIB);
				sk_X509_free(signers);
				return 0;
				}
			X509_STORE_CTX_set_default(&cert_ctx, "smime_sign");
		} else if(!X509_STORE_CTX_init (&cert_ctx, store, signer, NULL)) {
			PKCS7err(PKCS7_F_PKCS7_VERIFY,ERR_R_X509_LIB);
			sk_X509_free(signers);
			return 0;
		}
		if (!(flags & PKCS7_NOCRL))
			X509_STORE_CTX_set0_crls(&cert_ctx, p7->d.sign->crl);
		i = X509_verify_cert(&cert_ctx);
		if (i <= 0) j = X509_STORE_CTX_get_error(&cert_ctx);
		X509_STORE_CTX_cleanup(&cert_ctx);
		if (i <= 0) {
			PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_CERTIFICATE_VERIFY_ERROR);
			ERR_add_error_data(2, "Verify error:",
					 X509_verify_cert_error_string(j));
			sk_X509_free(signers);
			return 0;
		}
		/* Check for revocation status here */
	}

	/* Performance optimization: if the content is a memory BIO then
	 * store its contents in a temporary read only memory BIO. This
	 * avoids potentially large numbers of slow copies of data which will
	 * occur when reading from a read write memory BIO when signatures
	 * are calculated.
	 */

	if (indata && (BIO_method_type(indata) == BIO_TYPE_MEM))
		{
		char *ptr;
		long len;
		len = BIO_get_mem_data(indata, &ptr);
		tmpin = BIO_new_mem_buf(ptr, len);
		if (tmpin == NULL)
			{
			PKCS7err(PKCS7_F_PKCS7_VERIFY,ERR_R_MALLOC_FAILURE);
			return 0;
			}
		}
	else
		tmpin = indata;
		

	if (!(p7bio=PKCS7_dataInit(p7,tmpin)))
		goto err;

	if(flags & PKCS7_TEXT) {
		if(!(tmpout = BIO_new(BIO_s_mem()))) {
			PKCS7err(PKCS7_F_PKCS7_VERIFY,ERR_R_MALLOC_FAILURE);
			goto err;
		}
		BIO_set_mem_eof_return(tmpout, 0);
	} else tmpout = out;

	/* We now have to 'read' from p7bio to calculate digests etc. */
	for (;;)
	{
		i=BIO_read(p7bio,buf,sizeof(buf));
		if (i <= 0) break;
		if (tmpout) BIO_write(tmpout, buf, i);
	}

	if(flags & PKCS7_TEXT) {
		if(!SMIME_text(tmpout, out)) {
			PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_SMIME_TEXT_ERROR);
			BIO_free(tmpout);
			goto err;
		}
		BIO_free(tmpout);
	}

	/* Now Verify All Signatures */
	if (!(flags & PKCS7_NOSIGS))
	    for (i=0; i<sk_PKCS7_SIGNER_INFO_num(sinfos); i++)
		{
		si=sk_PKCS7_SIGNER_INFO_value(sinfos,i);
		signer = sk_X509_value (signers, i);
		j=PKCS7_signatureVerify(p7bio,p7,si, signer);
		if (j <= 0) {
			PKCS7err(PKCS7_F_PKCS7_VERIFY,PKCS7_R_SIGNATURE_FAILURE);
			goto err;
		}
	}

	ret = 1;

	err:
	
	if (tmpin == indata)
		{
		if (indata) BIO_pop(p7bio);
		}
	BIO_free_all(p7bio);

	sk_X509_free(signers);

	return ret;
}
