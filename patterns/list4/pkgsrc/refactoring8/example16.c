const struct builtin shbuiltins [] = {
	{"*=.", c_dot},
	{"*=:", c_label},
	{"[", c_test},
	{"*=break", c_brkcont},
	{"=builtin", c_builtin},
	{"*=continue", c_brkcont},
	{"*=eval", c_eval},
	{"*=exec", c_exec},
	{"*=exit", c_exitreturn},
	{"+false", c_label},
	{"*=return", c_exitreturn},
	{"*=set", c_set},
	{"*=shift", c_shift},
	{"=times", c_times},
	{"*=trap", c_trap},
	{"+=wait", c_wait},
	{"+read", c_read},
	{"test", c_test},
	{"+true", c_label},
	{"ulimit", c_ulimit},
	{"+umask", c_umask},
	{"*=unset", c_unset},
#ifdef OS2
	/* In OS2, the first line of a file can be "extproc name", which
	 * tells the command interpreter (cmd.exe) to use name to execute
	 * the file.  For this to be useful, ksh must ignore commands
	 * starting with extproc and this does the trick...
	 */
	{"extproc", c_label},
#endif /* OS2 */
	{NULL, NULL}
};
