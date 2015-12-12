static struct getargs args[] = {
    {	"principal", 	'p',	arg_string,	&client_name,
	"principal to authenticate as", NULL },
    {   "keytab",	'K',	arg_string,	&keytab,
   	"keytab for authentication principal", NULL },
    {
	"config-file",	'c',	arg_string,	&config_file,
	"location of config file",	"file"
    },
    {
	"key-file",	'k',	arg_string, &keyfile,
	"location of master key file", "file"
    },
    {
	"realm",	'r',	arg_string,   &realm,
	"realm to use", "realm"
    },
    {
	"admin-server",	'a',	arg_string,   &admin_server,
	"server to contact", "host"
    },
    {
	"server-port",	's',	arg_integer,   &server_port,
	"port to use", "port number"
    },
    {	"ad", 		0, arg_flag, &ad_flag, "active directory admin mode",
	NULL },
#ifdef HAVE_DLOPEN
    { "check-library", 0, arg_string, &check_library,
      "library to load password check function from", "library" },
    { "check-function", 0, arg_string, &check_function,
      "password check function to load", "function" },
    { "policy-libraries", 0, arg_strings, &policy_libraries,
      "password check function to load", "function" },
#endif
    {	"local", 'l', arg_flag, &local_flag, "local admin mode", NULL },
    {	"help",		'h',	arg_flag,   &help_flag, NULL, NULL },
    {	"version",	'v',	arg_flag,   &version_flag, NULL, NULL }
};
