#ifdef MANAGMENT_EXTERNAL_KEY
if((options->management_flags & MF_EXTERNAL_KEY) && options->priv_key_file)
	   {
		 msg (M_USAGE, "--key and --management-external-key are mutually exclusive");
	   }
	 else
#endif
#ifdef ENABLE_CRYPTOAPI
     if (options->cryptoapi_cert)
	{
	  if ((!(options->ca_file)) && (!(options->ca_path)))
	    msg(M_USAGE, "You must define CA file (--ca) or CA path (--capath)");
          if (options->cert_file)
	    msg(M_USAGE, "Parameter --cert cannot be used when --cryptoapicert is also specified.");
          if (options->priv_key_file)
	    msg(M_USAGE, "Parameter --key cannot be used when --cryptoapicert is also specified.");
          if (options->pkcs12_file)
	    msg(M_USAGE, "Parameter --pkcs12 cannot be used when --cryptoapicert is also specified.");
#ifdef MANAGMENT_EXTERNAL_KEY
          if (options->management_flags & MF_EXTERNAL_KEY)
	    msg(M_USAGE, "Parameter --management-external-key cannot be used when --cryptoapicert is also specified.");
#endif
	}
      else
#endif
      if (options->pkcs12_file)
        {
#ifdef ENABLE_CRYPTO_POLARSSL
	  msg(M_USAGE, "Parameter --pkcs12 cannot be used with the PolarSSL version version of OpenVPN.");
#else
          if (options->ca_path)
	    msg(M_USAGE, "Parameter --capath cannot be used when --pkcs12 is also specified.");
          if (options->cert_file)
	    msg(M_USAGE, "Parameter --cert cannot be used when --pkcs12 is also specified.");
          if (options->priv_key_file)
	    msg(M_USAGE, "Parameter --key cannot be used when --pkcs12 is also specified.");
#ifdef MANAGMENT_EXTERNAL_KEY
          if (options->management_flags & MF_EXTERNAL_KEY)
	    msg(M_USAGE, "Parameter --external-management-key cannot be used when --pkcs12 is also specified.");
#endif
#endif
        }
      else
        {
#ifdef ENABLE_CRYPTO_POLARSSL
	  if (!(options->ca_file))
	    msg(M_USAGE, "You must define CA file (--ca)");
          if (options->ca_path)
            msg(M_USAGE, "Parameter --capath cannot be used with the PolarSSL version version of OpenVPN.");
#else
	  if ((!(options->ca_file)) && (!(options->ca_path)))
	    msg(M_USAGE, "You must define CA file (--ca) or CA path (--capath)");
#endif
	  if (pull)
	    {

	      const int sum = (options->cert_file != NULL) +
#ifdef MANAGMENT_EXTERNAL_KEY
			((options->priv_key_file != NULL) || (options->management_flags & MF_EXTERNAL_KEY));
#else
		    (options->priv_key_file != NULL);
#endif


	      if (sum == 0)
		{
#if P2MP
		  if (!options->auth_user_pass_file)
#endif
		    msg (M_USAGE, "No client-side authentication method is specified.  You must use either --cert/--key, --pkcs12, or --auth-user-pass");
		}
	      else if (sum == 2)
		;
	      else
		{
		  msg (M_USAGE, "If you use one of --cert or --key, you must use them both");
		}
	    }
	  else
	    {
	      notnull (options->cert_file, "certificate file (--cert) or PKCS#12 file (--pkcs12)");
#ifdef MANAGMENT_EXTERNAL_KEY
          if (!(options->management_flags & MF_EXTERNAL_KEY))
#endif
	      notnull (options->priv_key_file, "private key file (--key) or PKCS#12 file (--pkcs12)");
	    }
	}
