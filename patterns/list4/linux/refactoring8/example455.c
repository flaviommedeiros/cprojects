static const char *keyring_name[INTEGRITY_KEYRING_MAX] = {
	"_evm",
	"_module",
#ifndef CONFIG_IMA_TRUSTED_KEYRING
	"_ima",
#else
	".ima",
#endif
};
