#ifdef CONFIG_ISDN_AUDIO
if (!info->vonline)
#endif
				isdn_tty_check_esc(buf, m->mdmreg[REG_ESC], c,
						   &(m->pluscount),
						   &(m->lastplus));
