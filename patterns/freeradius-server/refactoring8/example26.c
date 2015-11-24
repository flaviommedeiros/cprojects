static int CC_HINT(nonnull (1, 2, 4, 5 ,6)) do_mschap(rlm_mschap_t *inst, REQUEST *request, VALUE_PAIR *password,
						      uint8_t const *challenge, uint8_t const *response,
						      uint8_t nthashhash[NT_DIGEST_LENGTH], MSCHAP_AUTH_METHOD method)
{
	uint8_t	calculated[24];

	memset(nthashhash, 0, NT_DIGEST_LENGTH);

	switch (method) {
	case AUTH_INTERNAL:
	/*
	 *	Do normal authentication.
	 */
		{
		/*
		 *	No password: can't do authentication.
		 */
		if (!password) {
			REDEBUG("FAILED: No NT/LM-Password.  Cannot perform authentication");
			return -1;
		}

		smbdes_mschap(password->vp_octets, challenge, calculated);
		if (rad_digest_cmp(response, calculated, 24) != 0) {
			return -1;
		}

		/*
		 *	If the password exists, and is an NT-Password,
		 *	then calculate the hash of the NT hash.  Doing this
		 *	here minimizes work for later.
		 */
		if (!password->da->vendor &&
		    (password->da->attr == PW_NT_PASSWORD)) {
			fr_md4_calc(nthashhash, password->vp_octets, MD4_DIGEST_LENGTH);
		}

		break;
		}
	case AUTH_NTLMAUTH_EXEC:
	/*
	 *	Run ntlm_auth
	 */
		{
		int	result;
		char	buffer[256];
		size_t	len;

		/*
		 *	Run the program, and expect that we get 16
		 */
		result = radius_exec_program(request, buffer, sizeof(buffer), NULL, request, inst->ntlm_auth, NULL,
					     true, true, inst->ntlm_auth_timeout);
		if (result != 0) {
			char *p;

			/*
			 *	look for "Password expired", or "Must change password".
			 */
			if (strcasestr(buffer, "Password expired") ||
			    strcasestr(buffer, "Must change password")) {
				REDEBUG2("%s", buffer);
				return -648;
			}

			if (strcasestr(buffer, "Account locked out") ||
			    strcasestr(buffer, "0xC0000234")) {
				REDEBUG2("%s", buffer);
				return -647;
			}

			if (strcasestr(buffer, "Account disabled") ||
			    strcasestr(buffer, "0xC0000072")) {
				REDEBUG2("%s", buffer);
				return -691;
			}

			RDEBUG2("External script failed");
			p = strchr(buffer, '\n');
			if (p) *p = '\0';

			REDEBUG("External script says: %s", buffer);
			return -1;
		}

		/*
		 *	Parse the answer as an nthashhash.
		 *
		 *	ntlm_auth currently returns:
		 *	NT_KEY: 000102030405060708090a0b0c0d0e0f
		 */
		if (memcmp(buffer, "NT_KEY: ", 8) != 0) {
			REDEBUG("Invalid output from ntlm_auth: expecting 'NT_KEY: ' prefix");
			return -1;
		}

		/*
		 *	Check the length.  It should be at least 32, with an LF at the end.
		 */
		len = strlen(buffer + 8);
		if (len < 32) {
			REDEBUG2("Invalid output from ntlm_auth: NT_KEY too short, expected 32 bytes got %zu bytes",
				 len);

			return -1;
		}

		/*
		 *	Update the NT hash hash, from the NT key.
		 */
		if (fr_hex2bin(nthashhash, NT_DIGEST_LENGTH, buffer + 8, len) != NT_DIGEST_LENGTH) {
			REDEBUG("Invalid output from ntlm_auth: NT_KEY has non-hex values");
			return -1;
		}

		break;
		}
#ifdef WITH_AUTH_WINBIND
	case AUTH_WBCLIENT:
	/*
	 *	Process auth via the wbclient library
	 */
		return do_auth_wbclient(inst, request, challenge, response, nthashhash);
#endif
	default:
		/* We should never reach this line */
		RERROR("Internal error: Unknown mschap auth method (%d)", method);
		return -1;
	}

	return 0;
}
