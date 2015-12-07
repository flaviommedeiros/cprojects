#ifdef INETD_BUILTINS_ENABLED
if (sep->se_builtin == NULL
			 || (sep->se_socktype == SOCK_STREAM
			     && sep->se_builtin->bi_fork))
#endif
			{
				if (sep->se_max != 0) {
					if (++sep->se_count == 1)
						sep->se_time = monotonic_sec();
					else if (sep->se_count >= sep->se_max) {
						unsigned now = monotonic_sec();
						/* did we accumulate se_max connects too quickly? */
						if (now - sep->se_time <= CNT_INTERVAL) {
							bb_error_msg("%s/%s: too many connections, pausing",
									sep->se_service, sep->se_proto);
							remove_fd_from_set(sep->se_fd);
							close(sep->se_fd);
							sep->se_fd = -1;
							sep->se_count = 0;
							rearm_alarm(); /* will revive it in RETRYTIME sec */
							restore_sigmask(&omask);
							maybe_close(new_udp_fd);
							maybe_close(accepted_fd);
							continue; /* -> check next fd in fd set */
						}
						sep->se_count = 0;
					}
				}
				/* on NOMMU, streamed chargen
				 * builtin wouldn't work, but it is
				 * not allowed on NOMMU (ifdefed out) */
#ifdef INETD_BUILTINS_ENABLED
				if (BB_MMU && sep->se_builtin)
					pid = fork();
				else
#endif
					pid = vfork();

				if (pid < 0) { /* fork error */
					bb_perror_msg("vfork"+1);
					sleep(1);
					restore_sigmask(&omask);
					maybe_close(new_udp_fd);
					maybe_close(accepted_fd);
					continue; /* -> check next fd in fd set */
				}
				if (pid == 0)
					pid--; /* -1: "we did fork and we are child" */
			}
