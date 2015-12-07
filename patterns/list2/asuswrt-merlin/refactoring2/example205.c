#ifdef CONFIG_CIFS_WEAK_PW_HASH
if ((secFlags & CIFSSEC_MAY_PLNTXT) == 0)
#endif /* CIFS_WEAK_PW_HASH */
			cERROR(1, ("Server requests plain text password"
				  " but client support disabled"));
