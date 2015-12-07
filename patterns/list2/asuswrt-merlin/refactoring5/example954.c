#ifdef CONFIG_CIFS_WEAK_PW_HASH
if ((extended_security & CIFSSEC_MAY_LANMAN) &&
			(ses->server->secType == LANMAN))
			calc_lanman_hash(ses, bcc_ptr);
		else
#endif /* CIFS_WEAK_PW_HASH */
		SMBNTencrypt(ses->password,
			     ses->server->cryptKey,
			     bcc_ptr);
