if (gtp_access_cooked_clock
#ifdef CONFIG_X86
				    || gtp_access_cooked_rdtsc
#endif
#ifdef GTP_PERF_EVENTS
				    || gtp_have_pc_pe
#endif
				)
					tpe->u.kp.kpret.handler = gtp_kp_ret_handler_plus;
				else
					tpe->u.kp.kpret.handler = gtp_kp_ret_handler;
