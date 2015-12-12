static struct getargs args[] = {
    {
	"cache-name",	0,	arg_string,	&system_cache_name,
	"system cache name", "cachename"
    },
    {
	"config-file",	'c',	arg_string,	&config_file,
	"location of config file",	"file"
    },
    {
	"group",	'g',	arg_string,	&system_group,
	"system cache group",	"group"
    },
    {
	"max-request",	0,	arg_string, &max_request,
	"max size for a kcm-request", "size"
    },
    {
	"launchd",	0,	arg_flag, &launchd_flag,
	"when in use by launchd", NULL
    },
    {
	"detach",       0 ,      arg_flag, &detach_from_console,
	"detach from console", NULL
    },
    {
        "daemon-child",       0 ,      arg_integer, &daemon_child,
        "private argument, do not use", NULL
    },
    {	"help",		'h',	arg_flag,   &help_flag, NULL, NULL },
    {
	"system-principal",	'k',	arg_string,	&system_principal,
	"system principal name",	"principal"
    },
    {
	"lifetime",	'l', arg_string, &ticket_life,
	"lifetime of system tickets", "time"
    },
    {
	"mode",		'm', arg_string, &system_perms,
	"octal mode of system cache", "mode"
    },
    {
	"name-constraints",	'n', arg_negative_flag, &name_constraints,
	"disable credentials cache name constraints", NULL
    },
    {
	"disallow-getting-krbtgt", 0, arg_flag, &disallow_getting_krbtgt,
	"disable fetching krbtgt from the cache", NULL
    },
    {
	"renewable-life",	'r', arg_string, &renew_life,
    	"renewable lifetime of system tickets", "time"
    },
    {
	"socket-path",		's', arg_string, &socket_path,
    	"path to kcm domain socket", "path"
    },
#ifdef HAVE_DOOR_CREATE
    {
	"door-path",		's', arg_string, &door_path,
    	"path to kcm door", "path"
    },
#endif
    {
	"server",		'S', arg_string, &system_server,
    	"server to get system ticket for", "principal"
    },
    {
	"keytab",	't',	arg_string,	&system_keytab,
	"system keytab name",	"keytab"
    },
    {
	"user",		'u',	arg_string,	&system_user,
	"system cache owner",	"user"
    },
    {	"version",	'v',	arg_flag,   &version_flag, NULL, NULL }
};
