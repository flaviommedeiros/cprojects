if (!o->persist_key
#ifdef ENABLE_PKCS11
	&& !o->pkcs11_id
#endif
	)
     msg (M_WARN, "WARNING: you are using user/group/chroot/setcon without persist-key -- this may cause restarts to fail");
