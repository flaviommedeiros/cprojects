#ifdef CONFIG_X86
if (tpe->step || gtp_have_step)
#else
					if (tpe->step)
#endif
						tpe->u.kp.kpret.kp.post_handler = gtp_kp_post_handler;
