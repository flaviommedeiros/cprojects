#ifdef CONFIG_CIFS_WEAK_PW_HASH
if ((global_secflags & CIFSSEC_MAY_LANMAN) &&
		    (ses->sectype == LANMAN))
			calc_lanman_hash(tcon->password, ses->server->cryptkey,
					 ses->server->sec_mode &
					    SECMODE_PW_ENCRYPT ? true : false,
					 bcc_ptr);
		else
#endif /* CIFS_WEAK_PW_HASH */
		rc = SMBNTencrypt(tcon->password, ses->server->cryptkey,
					bcc_ptr, nls_codepage);
