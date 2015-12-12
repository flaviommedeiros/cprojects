struct salt_type _krb5_des_salt[] = {
    {
	KRB5_PW_SALT,
	"pw-salt",
	krb5_DES_string_to_key
    },
#ifdef ENABLE_AFS_STRING_TO_KEY
    {
	KRB5_AFS3_SALT,
	"afs3-salt",
	DES_AFS3_string_to_key
    },
#endif
    { 0, NULL, NULL }
};
