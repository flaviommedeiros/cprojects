#ifdef CONFIG_CIFS_WEAK_PW_HASH
if ((secFlags & CIFSSEC_MAY_PLNTXT) == 0)
#endif /* CIFS_WEAK_PW_HASH */
			cifs_dbg(VFS, "Server requests plain text password but client support disabled\n");
