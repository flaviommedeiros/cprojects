switch (*input) {
	case '\0':
		r_core_cmd_repeat (core, 0);
		break;
	case ':':
		if ((ptr = strchr (input+1, ' '))) {
			/* .:port cmd */
			/* .:host:port cmd */
			cmd = ptr+1;
			*ptr = 0;
			eol = strchr (input+1, ':');
			if (eol) {
				*eol = 0;
				host = input+1;
				port = eol+1;
			} else {
				host = "localhost";
				port = input+((input[1]==':')?2:1);
			}
			rbuf = r_core_rtr_cmds_query (core, host, port, cmd);
			if (rbuf) {
				r_cons_printf ("%s", rbuf);
				free (rbuf);
			}
		} else r_core_rtr_cmds (core, input+1);
		break;
	case '.': // same as \n
		r_core_cmd_repeat (core, 1);
		break;
	case '-':
		if (input[1]=='?') {
			r_cons_printf ("Usage: '-' '.-' '. -' do the same\n");
		} else r_core_run_script (core, "-");
		break;
	case ' ':
		if (!r_core_run_script (core, input+1)) {
			eprintf ("Cannot find '%s'\n", input+1);
			core->num->value = 1;
		} else {
			core->num->value = 0;
		}
		break;
	case '!':
		/* from command */
		r_core_cmd_command (core, input+1);
		break;
	case '(':
		r_cmd_macro_call (&core->rcmd->macro, input+1);
		break;
	case '?':{
		const char* help_msg[] = {
		"Usage:", ".[r2cmd] | [file] | [!command] | [(macro)]", " # define macro or load r2, cparse or rlang file",
		".", "", "repeat last command backward",
		".", "r2cmd", "interpret the output of the command as r2 commands",
		"..", "", "repeat last command forward (same as \\n)",
		".:", "8080", "listen for commands on given tcp port",
		".", " foo.r2", "interpret r2 script",
		".-", "", "open cfg.editor and interpret tmp file",
		".!", "rabin -ri $FILE", "interpret output of command",
		".", "(foo 1 2 3)", "run macro 'foo' with args 1, 2, 3",
		"./", " ELF", "interpret output of command /m ELF as r. commands",
		NULL};
		r_core_cmd_help (core, help_msg);
		}
		break;
#if 1
	case '0'...'9':
		eprintf ("|ERROR| No .[0..9] to avoid infinite loops\n");
		break;
#endif
	default:
		inp = strdup (input);
		filter = strchr (inp, '~');
		if (filter) *filter = 0;
		ptr = str = r_core_cmd_str (core, inp);
		if (filter) *filter = '~';
		r_cons_break (NULL, NULL);
		if (ptr)
		for (;;) {
			if (r_cons_singleton()->breaked) break;
			eol = strchr (ptr, '\n');
			if (eol) *eol = '\0';
			if (*ptr) {
				char *p = r_str_concat (strdup (ptr), filter);
				r_core_cmd0 (core, p);
				free (p);
			}
			if (!eol) break;
			ptr = eol+1;
		}
		r_cons_break_end ();
		free (str);
		free (inp);
		break;
	}
