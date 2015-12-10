switch(op) {
	case C_EQ: a = (strcmp(s1,s2) == 0); break;
	case C_NE: a = (strcmp(s1,s2) != 0); break;
	case C_GT: a = (strcmp(s1,s2) >  0); break;
	case C_GE: a = (strcmp(s1,s2) >= 0); break;
	case C_LT: a = (strcmp(s1,s2) <  0); break;
	case C_LE: a = (strcmp(s1,s2) <= 0); break;
#ifdef PCRE_SUPPORT
	case C_RE_EQ:
	case C_RE_NE:
		{
			int inputlen = (int)strlen(s1);
			pcre *compiled_regex;
			pcre_extra *extra_regex;
			const char *pcre_error, *pcre_match;
			int pcre_erroroffset, offsetcount, i;
			int offsets[256*3]; // (max_capturing_groups+1)*3

			compiled_regex = libpcre->compile(s2, 0, &pcre_error, &pcre_erroroffset, NULL);

			if( compiled_regex == NULL ) {
				ShowError("script:op2_str: Invalid regex '%s'.\n", s2);
				script->reportsrc(st);
				script_pushnil(st);
				st->state = END;
				return;
			}

			extra_regex = libpcre->study(compiled_regex, 0, &pcre_error);

			if( pcre_error != NULL ) {
				libpcre->free(compiled_regex);
				ShowError("script:op2_str: Unable to optimize the regex '%s': %s\n", s2, pcre_error);
				script->reportsrc(st);
				script_pushnil(st);
				st->state = END;
				return;
			}

			offsetcount = libpcre->exec(compiled_regex, extra_regex, s1, inputlen, 0, 0, offsets, 256*3);

			if( offsetcount == 0 ) {
				offsetcount = 256;
			} else if( offsetcount == PCRE_ERROR_NOMATCH ) {
				offsetcount = 0;
			} else if( offsetcount < 0 ) {
				libpcre->free(compiled_regex);
				if( extra_regex != NULL )
					libpcre->free(extra_regex);
				ShowWarning("script:op2_str: Unable to process the regex '%s'.\n", s2);
				script->reportsrc(st);
				script_pushnil(st);
				st->state = END;
				return;
			}

			if( op == C_RE_EQ ) {
				for( i = 0; i < offsetcount; i++ ) {
					libpcre->get_substring(s1, offsets, offsetcount, i, &pcre_match);
					mapreg->setregstr(reference_uid(script->add_str("$@regexmatch$"), i), pcre_match);
					libpcre->free_substring(pcre_match);
				}
				mapreg->setreg(script->add_str("$@regexmatchcount"), i);
				a = offsetcount;
			} else { // C_RE_NE
				a = (offsetcount == 0);
			}
			libpcre->free(compiled_regex);
			if( extra_regex != NULL )
				libpcre->free(extra_regex);
		}
		break;
#endif // PCRE_SUPPORT
	case C_ADD:
		{
			char* buf = (char *)aMalloc((strlen(s1)+strlen(s2)+1)*sizeof(char));
			strcpy(buf, s1);
			strcat(buf, s2);
			script_pushstr(st, buf);
			return;
		}
	default:
		ShowError("script:op2_str: unexpected string operator %s\n", script->op2name(op));
		script->reportsrc(st);
		script_pushnil(st);
		st->state = END;
		return;
	}
