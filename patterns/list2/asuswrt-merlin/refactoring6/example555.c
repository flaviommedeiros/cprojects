if (o->username || o->groupname || o->chroot_dir
#ifdef ENABLE_SELINUX
      || o->selinux_context
#endif
      )
   {
    if (!o->persist_tun)
     msg (M_WARN, "WARNING: you are using user/group/chroot/setcon without persist-tun -- this may cause restarts to fail");
    if (!o->persist_key
#ifdef ENABLE_PKCS11
	&& !o->pkcs11_id
#endif
	)
     msg (M_WARN, "WARNING: you are using user/group/chroot/setcon without persist-key -- this may cause restarts to fail");
   }
