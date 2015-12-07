#if P2MP
if (!options->auth_user_pass_file)
#endif
		    msg (M_USAGE, "No client-side authentication method is specified.  You must use either --cert/--key, --pkcs12, or --auth-user-pass");
