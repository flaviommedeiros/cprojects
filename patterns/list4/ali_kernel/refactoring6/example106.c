if (gtp_access_cooked_clock
#ifdef CONFIG_X86
				    || gtp_access_cooked_rdtsc
#endif
#ifdef GTP_PERF_EVENTS
				    || gtp_have_pc_pe
#endif
				) {
#ifdef CONFIG_X86
					if (tpe->step || gtp_have_step) {
#else
					if (tpe->step) {
#endif
						tpe->u.kp.kpret.kp.pre_handler = gtp_kp_pre_handler_plus_step;
						tpe->u.kp.kpret.kp.post_handler = gtp_kp_post_handler_plus;
					} else
						tpe->u.kp.kpret.kp.pre_handler = gtp_kp_pre_handler_plus;
				} else {
					tpe->u.kp.kpret.kp.pre_handler = gtp_kp_pre_handler;
#ifdef CONFIG_X86
					if (tpe->step || gtp_have_step)
#else
					if (tpe->step)
#endif
						tpe->u.kp.kpret.kp.post_handler = gtp_kp_post_handler;
				}
				ret = register_kprobe(&tpe->u.kp.kpret.kp);
			}
