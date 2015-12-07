#ifdef HAVE_KRB5
if (!(ads->auth.flags & ADS_AUTH_DISABLE_KERBEROS) &&
	    got_kerberos_mechanism) 
	{
		struct ads_service_principal p;

		status = ads_generate_service_principal(ads, given_principal, &p);
		SAFE_FREE(given_principal);
		if (!ADS_ERR_OK(status)) {
			return status;
		}

		status = ads_sasl_spnego_krb5_bind(ads, &p);
		if (ADS_ERR_OK(status)) {
			ads_free_service_principal(&p);
			return status;
		}

		DEBUG(10,("ads_sasl_spnego_krb5_bind failed with: %s, "
			  "calling kinit\n", ads_errstr(status)));

		status = ADS_ERROR_KRB5(ads_kinit_password(ads)); 

		if (ADS_ERR_OK(status)) {
			status = ads_sasl_spnego_krb5_bind(ads, &p);
			if (!ADS_ERR_OK(status)) {
				DEBUG(0,("kinit succeeded but "
					"ads_sasl_spnego_krb5_bind failed: %s\n",
					ads_errstr(status)));
			}
		}

		ads_free_service_principal(&p);

		/* only fallback to NTLMSSP if allowed */
		if (ADS_ERR_OK(status) || 
		    !(ads->auth.flags & ADS_AUTH_ALLOW_NTLMSSP)) {
			return status;
		}
	} else
#endif
	{
		SAFE_FREE(given_principal);
	}
