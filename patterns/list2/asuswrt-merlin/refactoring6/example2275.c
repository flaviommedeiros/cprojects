if (
#if 0
!krb5_checksum_is_keyed(context, auth->cksum->cksumtype)
	||
#endif
 !krb5_checksum_is_collision_proof(context, auth->cksum->cksumtype)) {
	kdc_log(context, config, 0, "Bad checksum type in authenticator: %d",
		auth->cksum->cksumtype);
	ret =  KRB5KRB_AP_ERR_INAPP_CKSUM;
	goto out;
    }
