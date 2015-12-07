#ifdef WITH_PAM
if (!lp_pam_password_change()) {
#endif

			if((lp_passwd_program() == NULL) ||
			   (strlen(lp_passwd_program()) == 0))
			{
				fprintf( stderr, "ERROR: the 'unix password sync' parameter is set and there is no valid 'passwd program' \
parameter.\n" );
				ret = 1;
			} else {
				const char *passwd_prog;
				char *truncated_prog = NULL;
				const char *p;

				passwd_prog = lp_passwd_program();
				p = passwd_prog;
				next_token_talloc(talloc_tos(),
						&p,
						&truncated_prog, NULL);
				if (truncated_prog && access(truncated_prog, F_OK) == -1) {
					fprintf(stderr, "ERROR: the 'unix password sync' parameter is set and the 'passwd program' (%s) \
cannot be executed (error was %s).\n", truncated_prog, strerror(errno) );
					ret = 1;
				}
			}

#ifdef WITH_PAM
		}
