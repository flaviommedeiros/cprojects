#ifdef INETD_BUILTINS_ENABLED
if (BB_MMU && sep->se_builtin)
					pid = fork();
				else
#endif
					pid = vfork();
