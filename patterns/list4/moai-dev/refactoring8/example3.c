static int do_body(X509 **xret, EVP_PKEY *pkey, X509 *x509, const EVP_MD *dgst,
	     STACK_OF(CONF_VALUE) *policy, CA_DB *db, BIGNUM *serial, char *subj,
	     unsigned long chtype, int multirdn,
	     int email_dn, char *startdate, char *enddate, long days, int batch,
	     int verbose, X509_REQ *req, char *ext_sect, CONF *lconf,
	     unsigned long certopt, unsigned long nameopt, int default_op,
	     int ext_copy, int selfsign)
	{
	X509_NAME *name=NULL,*CAname=NULL,*subject=NULL, *dn_subject=NULL;
	ASN1_UTCTIME *tm,*tmptm;
	ASN1_STRING *str,*str2;
	ASN1_OBJECT *obj;
	X509 *ret=NULL;
	X509_CINF *ci;
	X509_NAME_ENTRY *ne;
	X509_NAME_ENTRY *tne,*push;
	EVP_PKEY *pktmp;
	int ok= -1,i,j,last,nid;
	const char *p;
	CONF_VALUE *cv;
	OPENSSL_STRING row[DB_NUMBER];
	OPENSSL_STRING *irow=NULL;
	OPENSSL_STRING *rrow=NULL;
	char buf[25];

	tmptm=ASN1_UTCTIME_new();
	if (tmptm == NULL)
		{
		BIO_printf(bio_err,"malloc error\n");
		return(0);
		}

	for (i=0; i<DB_NUMBER; i++)
		row[i]=NULL;

	if (subj)
		{
		X509_NAME *n = parse_name(subj, chtype, multirdn);

		if (!n)
			{
			ERR_print_errors(bio_err);
			goto err;
			}
		X509_REQ_set_subject_name(req,n);
		req->req_info->enc.modified = 1;
		X509_NAME_free(n);
		}

	if (default_op)
		BIO_printf(bio_err,"The Subject's Distinguished Name is as follows\n");

	name=X509_REQ_get_subject_name(req);
	for (i=0; i<X509_NAME_entry_count(name); i++)
		{
		ne= X509_NAME_get_entry(name,i);
		str=X509_NAME_ENTRY_get_data(ne);
		obj=X509_NAME_ENTRY_get_object(ne);

		if (msie_hack)
			{
			/* assume all type should be strings */
			nid=OBJ_obj2nid(ne->object);

			if (str->type == V_ASN1_UNIVERSALSTRING)
				ASN1_UNIVERSALSTRING_to_string(str);

			if ((str->type == V_ASN1_IA5STRING) &&
				(nid != NID_pkcs9_emailAddress))
				str->type=V_ASN1_T61STRING;

			if ((nid == NID_pkcs9_emailAddress) &&
				(str->type == V_ASN1_PRINTABLESTRING))
				str->type=V_ASN1_IA5STRING;
			}

		/* If no EMAIL is wanted in the subject */
		if ((OBJ_obj2nid(obj) == NID_pkcs9_emailAddress) && (!email_dn))
			continue;

		/* check some things */
		if ((OBJ_obj2nid(obj) == NID_pkcs9_emailAddress) &&
			(str->type != V_ASN1_IA5STRING))
			{
			BIO_printf(bio_err,"\nemailAddress type needs to be of type IA5STRING\n");
			goto err;
			}
		if ((str->type != V_ASN1_BMPSTRING) && (str->type != V_ASN1_UTF8STRING))
			{
			j=ASN1_PRINTABLE_type(str->data,str->length);
			if (	((j == V_ASN1_T61STRING) &&
				 (str->type != V_ASN1_T61STRING)) ||
				((j == V_ASN1_IA5STRING) &&
				 (str->type == V_ASN1_PRINTABLESTRING)))
				{
				BIO_printf(bio_err,"\nThe string contains characters that are illegal for the ASN.1 type\n");
				goto err;
				}
			}

		if (default_op)
			old_entry_print(bio_err, obj, str);
		}

	/* Ok, now we check the 'policy' stuff. */
	if ((subject=X509_NAME_new()) == NULL)
		{
		BIO_printf(bio_err,"Memory allocation failure\n");
		goto err;
		}

	/* take a copy of the issuer name before we mess with it. */
	if (selfsign)
		CAname=X509_NAME_dup(name);
	else
		CAname=X509_NAME_dup(x509->cert_info->subject);
	if (CAname == NULL) goto err;
	str=str2=NULL;

	for (i=0; i<sk_CONF_VALUE_num(policy); i++)
		{
		cv=sk_CONF_VALUE_value(policy,i); /* get the object id */
		if ((j=OBJ_txt2nid(cv->name)) == NID_undef)
			{
			BIO_printf(bio_err,"%s:unknown object type in 'policy' configuration\n",cv->name);
			goto err;
			}
		obj=OBJ_nid2obj(j);

		last= -1;
		for (;;)
			{
			/* lookup the object in the supplied name list */
			j=X509_NAME_get_index_by_OBJ(name,obj,last);
			if (j < 0)
				{
				if (last != -1) break;
				tne=NULL;
				}
			else
				{
				tne=X509_NAME_get_entry(name,j);
				}
			last=j;

			/* depending on the 'policy', decide what to do. */
			push=NULL;
			if (strcmp(cv->value,"optional") == 0)
				{
				if (tne != NULL)
					push=tne;
				}
			else if (strcmp(cv->value,"supplied") == 0)
				{
				if (tne == NULL)
					{
					BIO_printf(bio_err,"The %s field needed to be supplied and was missing\n",cv->name);
					goto err;
					}
				else
					push=tne;
				}
			else if (strcmp(cv->value,"match") == 0)
				{
				int last2;

				if (tne == NULL)
					{
					BIO_printf(bio_err,"The mandatory %s field was missing\n",cv->name);
					goto err;
					}

				last2= -1;

again2:
				j=X509_NAME_get_index_by_OBJ(CAname,obj,last2);
				if ((j < 0) && (last2 == -1))
					{
					BIO_printf(bio_err,"The %s field does not exist in the CA certificate,\nthe 'policy' is misconfigured\n",cv->name);
					goto err;
					}
				if (j >= 0)
					{
					push=X509_NAME_get_entry(CAname,j);
					str=X509_NAME_ENTRY_get_data(tne);
					str2=X509_NAME_ENTRY_get_data(push);
					last2=j;
					if (ASN1_STRING_cmp(str,str2) != 0)
						goto again2;
					}
				if (j < 0)
					{
					BIO_printf(bio_err,"The %s field needed to be the same in the\nCA certificate (%s) and the request (%s)\n",cv->name,((str2 == NULL)?"NULL":(char *)str2->data),((str == NULL)?"NULL":(char *)str->data));
					goto err;
					}
				}
			else
				{
				BIO_printf(bio_err,"%s:invalid type in 'policy' configuration\n",cv->value);
				goto err;
				}

			if (push != NULL)
				{
				if (!X509_NAME_add_entry(subject,push, -1, 0))
					{
					if (push != NULL)
						X509_NAME_ENTRY_free(push);
					BIO_printf(bio_err,"Memory allocation failure\n");
					goto err;
					}
				}
			if (j < 0) break;
			}
		}

	if (preserve)
		{
		X509_NAME_free(subject);
		/* subject=X509_NAME_dup(X509_REQ_get_subject_name(req)); */
		subject=X509_NAME_dup(name);
		if (subject == NULL) goto err;
		}

	if (verbose)
		BIO_printf(bio_err,"The subject name appears to be ok, checking data base for clashes\n");

	/* Build the correct Subject if no e-mail is wanted in the subject */
	/* and add it later on because of the method extensions are added (altName) */
	 
	if (email_dn)
		dn_subject = subject;
	else
		{
		X509_NAME_ENTRY *tmpne;
		/* Its best to dup the subject DN and then delete any email
		 * addresses because this retains its structure.
		 */
		if (!(dn_subject = X509_NAME_dup(subject)))
			{
			BIO_printf(bio_err,"Memory allocation failure\n");
			goto err;
			}
		while((i = X509_NAME_get_index_by_NID(dn_subject,
					NID_pkcs9_emailAddress, -1)) >= 0)
			{
			tmpne = X509_NAME_get_entry(dn_subject, i);
			X509_NAME_delete_entry(dn_subject, i);
			X509_NAME_ENTRY_free(tmpne);
			}
		}

	if (BN_is_zero(serial))
		row[DB_serial]=BUF_strdup("00");
	else
		row[DB_serial]=BN_bn2hex(serial);
	if (row[DB_serial] == NULL)
		{
		BIO_printf(bio_err,"Memory allocation failure\n");
		goto err;
		}

	if (db->attributes.unique_subject)
		{
		OPENSSL_STRING *crow=row;

		rrow=TXT_DB_get_by_index(db->db,DB_name,crow);
		if (rrow != NULL)
			{
			BIO_printf(bio_err,
				"ERROR:There is already a certificate for %s\n",
				row[DB_name]);
			}
		}
	if (rrow == NULL)
		{
		rrow=TXT_DB_get_by_index(db->db,DB_serial,row);
		if (rrow != NULL)
			{
			BIO_printf(bio_err,"ERROR:Serial number %s has already been issued,\n",
				row[DB_serial]);
			BIO_printf(bio_err,"      check the database/serial_file for corruption\n");
			}
		}

	if (rrow != NULL)
		{
		BIO_printf(bio_err,
			"The matching entry has the following details\n");
		if (rrow[DB_type][0] == 'E')
			p="Expired";
		else if (rrow[DB_type][0] == 'R')
			p="Revoked";
		else if (rrow[DB_type][0] == 'V')
			p="Valid";
		else
			p="\ninvalid type, Data base error\n";
		BIO_printf(bio_err,"Type	  :%s\n",p);;
		if (rrow[DB_type][0] == 'R')
			{
			p=rrow[DB_exp_date]; if (p == NULL) p="undef";
			BIO_printf(bio_err,"Was revoked on:%s\n",p);
			}
		p=rrow[DB_exp_date]; if (p == NULL) p="undef";
		BIO_printf(bio_err,"Expires on    :%s\n",p);
		p=rrow[DB_serial]; if (p == NULL) p="undef";
		BIO_printf(bio_err,"Serial Number :%s\n",p);
		p=rrow[DB_file]; if (p == NULL) p="undef";
		BIO_printf(bio_err,"File name     :%s\n",p);
		p=rrow[DB_name]; if (p == NULL) p="undef";
		BIO_printf(bio_err,"Subject Name  :%s\n",p);
		ok= -1; /* This is now a 'bad' error. */
		goto err;
		}

	/* We are now totally happy, lets make and sign the certificate */
	if (verbose)
		BIO_printf(bio_err,"Everything appears to be ok, creating and signing the certificate\n");

	if ((ret=X509_new()) == NULL) goto err;
	ci=ret->cert_info;

#ifdef X509_V3
	/* Make it an X509 v3 certificate. */
	if (!X509_set_version(ret,2)) goto err;
#endif

	if (BN_to_ASN1_INTEGER(serial,ci->serialNumber) == NULL)
		goto err;
	if (selfsign)
		{
		if (!X509_set_issuer_name(ret,subject))
			goto err;
		}
	else
		{
		if (!X509_set_issuer_name(ret,X509_get_subject_name(x509)))
			goto err;
		}

	if (strcmp(startdate,"today") == 0)
		X509_gmtime_adj(X509_get_notBefore(ret),0);
	else ASN1_TIME_set_string(X509_get_notBefore(ret),startdate);

	if (enddate == NULL)
		X509_time_adj_ex(X509_get_notAfter(ret),days, 0, NULL);
	else ASN1_TIME_set_string(X509_get_notAfter(ret),enddate);

	if (!X509_set_subject_name(ret,subject)) goto err;

	pktmp=X509_REQ_get_pubkey(req);
	i = X509_set_pubkey(ret,pktmp);
	EVP_PKEY_free(pktmp);
	if (!i) goto err;

	/* Lets add the extensions, if there are any */
	if (ext_sect)
		{
		X509V3_CTX ctx;
		if (ci->version == NULL)
			if ((ci->version=ASN1_INTEGER_new()) == NULL)
				goto err;
		ASN1_INTEGER_set(ci->version,2); /* version 3 certificate */

		/* Free the current entries if any, there should not
		 * be any I believe */
		if (ci->extensions != NULL)
			sk_X509_EXTENSION_pop_free(ci->extensions,
						   X509_EXTENSION_free);

		ci->extensions = NULL;

		/* Initialize the context structure */
		if (selfsign)
			X509V3_set_ctx(&ctx, ret, ret, req, NULL, 0);
		else
			X509V3_set_ctx(&ctx, x509, ret, req, NULL, 0);

		if (extconf)
			{
			if (verbose)
				BIO_printf(bio_err, "Extra configuration file found\n");
 
			/* Use the extconf configuration db LHASH */
			X509V3_set_nconf(&ctx, extconf);
 
			/* Test the structure (needed?) */
			/* X509V3_set_ctx_test(&ctx); */

			/* Adds exts contained in the configuration file */
			if (!X509V3_EXT_add_nconf(extconf, &ctx, ext_sect,ret))
				{
				BIO_printf(bio_err,
				    "ERROR: adding extensions in section %s\n",
								ext_sect);
				ERR_print_errors(bio_err);
				goto err;
				}
			if (verbose)
				BIO_printf(bio_err, "Successfully added extensions from file.\n");
			}
		else if (ext_sect)
			{
			/* We found extensions to be set from config file */
			X509V3_set_nconf(&ctx, lconf);

			if(!X509V3_EXT_add_nconf(lconf, &ctx, ext_sect, ret))
				{
				BIO_printf(bio_err, "ERROR: adding extensions in section %s\n", ext_sect);
				ERR_print_errors(bio_err);
				goto err;
				}

			if (verbose) 
				BIO_printf(bio_err, "Successfully added extensions from config\n");
			}
		}

	/* Copy extensions from request (if any) */

	if (!copy_extensions(ret, req, ext_copy))
		{
		BIO_printf(bio_err, "ERROR: adding extensions from request\n");
		ERR_print_errors(bio_err);
		goto err;
		}

	/* Set the right value for the noemailDN option */
	if( email_dn == 0 )
		{
		if (!X509_set_subject_name(ret,dn_subject)) goto err;
		}

	if (!default_op)
		{
		BIO_printf(bio_err, "Certificate Details:\n");
		/* Never print signature details because signature not present */
		certopt |= X509_FLAG_NO_SIGDUMP | X509_FLAG_NO_SIGNAME;
		X509_print_ex(bio_err, ret, nameopt, certopt); 
		}

	BIO_printf(bio_err,"Certificate is to be certified until ");
	ASN1_TIME_print(bio_err,X509_get_notAfter(ret));
	if (days) BIO_printf(bio_err," (%ld days)",days);
	BIO_printf(bio_err, "\n");

	if (!batch)
		{

		BIO_printf(bio_err,"Sign the certificate? [y/n]:");
		(void)BIO_flush(bio_err);
		buf[0]='\0';
		if (!fgets(buf,sizeof(buf)-1,stdin))
			{
			BIO_printf(bio_err,"CERTIFICATE WILL NOT BE CERTIFIED: I/O error\n");
			ok=0;
			goto err;
			}
		if (!((buf[0] == 'y') || (buf[0] == 'Y')))
			{
			BIO_printf(bio_err,"CERTIFICATE WILL NOT BE CERTIFIED\n");
			ok=0;
			goto err;
			}
		}

	pktmp=X509_get_pubkey(ret);
	if (EVP_PKEY_missing_parameters(pktmp) &&
		!EVP_PKEY_missing_parameters(pkey))
		EVP_PKEY_copy_parameters(pktmp,pkey);
	EVP_PKEY_free(pktmp);

	if (!X509_sign(ret,pkey,dgst))
		goto err;

	/* We now just add it to the database */
	row[DB_type]=(char *)OPENSSL_malloc(2);

	tm=X509_get_notAfter(ret);
	row[DB_exp_date]=(char *)OPENSSL_malloc(tm->length+1);
	memcpy(row[DB_exp_date],tm->data,tm->length);
	row[DB_exp_date][tm->length]='\0';

	row[DB_rev_date]=NULL;

	/* row[DB_serial] done already */
	row[DB_file]=(char *)OPENSSL_malloc(8);
	row[DB_name]=X509_NAME_oneline(X509_get_subject_name(ret),NULL,0);

	if ((row[DB_type] == NULL) || (row[DB_exp_date] == NULL) ||
		(row[DB_file] == NULL) || (row[DB_name] == NULL))
		{
		BIO_printf(bio_err,"Memory allocation failure\n");
		goto err;
		}
	BUF_strlcpy(row[DB_file],"unknown",8);
	row[DB_type][0]='V';
	row[DB_type][1]='\0';

	if ((irow=(char **)OPENSSL_malloc(sizeof(char *)*(DB_NUMBER+1))) == NULL)
		{
		BIO_printf(bio_err,"Memory allocation failure\n");
		goto err;
		}

	for (i=0; i<DB_NUMBER; i++)
		{
		irow[i]=row[i];
		row[i]=NULL;
		}
	irow[DB_NUMBER]=NULL;

	if (!TXT_DB_insert(db->db,irow))
		{
		BIO_printf(bio_err,"failed to update database\n");
		BIO_printf(bio_err,"TXT_DB error number %ld\n",db->db->error);
		goto err;
		}
	ok=1;
err:
	for (i=0; i<DB_NUMBER; i++)
		if (row[i] != NULL) OPENSSL_free(row[i]);

	if (CAname != NULL)
		X509_NAME_free(CAname);
	if (subject != NULL)
		X509_NAME_free(subject);
	if ((dn_subject != NULL) && !email_dn)
		X509_NAME_free(dn_subject);
	if (tmptm != NULL)
		ASN1_UTCTIME_free(tmptm);
	if (ok <= 0)
		{
		if (ret != NULL) X509_free(ret);
		ret=NULL;
		}
	else
		*xret=ret;
	return(ok);
	}
