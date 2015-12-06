static
const struct bfg_set_device_definition dualminer_set_device_funcs[] = {
	{"dual_mode", dualminer_set_dual_mode, "set to 1 to enable dual algorithm mining"},
#ifdef USE_SCRYPT
	{"scrypt", dualminer_set_scrypt, "set to 1 to put in scrypt mode"},
#endif
	{NULL},
};
