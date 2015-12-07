#ifdef WITH_PAM
if (!lp_pam_password_change()) {
#endif

			if(lp_passwd_program() == NULL) {
				fprintf( stderr, "ERROR: the 'unix password sync' parameter is set and there is no valid 'passwd program' \
parameter.\n" );
				ret = 1;
			} else {
				pstring passwd_prog;
				pstring truncated_prog;
				const char *p;

				pstrcpy( passwd_prog, lp_passwd_program());
				p = passwd_prog;
				*truncated_prog = '\0';
				next_token(&p, truncated_prog, NULL, sizeof(pstring));

				if(access(truncated_prog, F_OK) == -1) {
					fprintf(stderr, "ERROR: the 'unix password sync' parameter is set and the 'passwd program' (%s) \
cannot be executed (error was %s).\n", truncated_prog, strerror(errno) );
					ret = 1;
				}

             }

#ifdef WITH_PAM
		}
