#ifdef CONFIG_CIFS_WEAK_PW_HASH
if ((global_secflags & CIFSSEC_MAY_LANMAN) &&
		    (ses->server->secType == LANMAN))
			calc_lanman_hash(tcon->password, ses->server->cryptKey,
					 ses->server->secMode &
					    SECMODE_PW_ENCRYPT ? true : false,
					 bcc_ptr);
		else
#endif /* CIFS_WEAK_PW_HASH */
		SMBNTencrypt(tcon->password, ses->server->cryptKey,
			     bcc_ptr);
