switch ((c = *wp++)) {
		  case EOS:
			return;
		  case CHAR:
			tputC(*wp++, shf);
			break;
		  case QCHAR:
			c = *wp++;
			if (!quoted || (c == '"' || c == '`' || c == '$'))
				tputc('\\', shf);
			tputC(c, shf);
			break;
		  case COMSUB:
			tputc('$', shf);
			tputc('(', shf);
			while (*wp != 0)
				tputC(*wp++, shf);
			tputc(')', shf);
			wp++;
			break;
		  case EXPRSUB:
			tputc('$', shf);
			tputc('(', shf);
			tputc('(', shf);
			while (*wp != 0)
				tputC(*wp++, shf);
			tputc(')', shf);
			tputc(')', shf);
			wp++;
			break;
		  case OQUOTE:
		  	quoted = 1;
			tputc('"', shf);
			break;
		  case CQUOTE:
			quoted = 0;
			tputc('"', shf);
			break;
		  case OSUBST:
			tputc('$', shf);
			if (*wp++ == '{')
				tputc('{', shf);
			while ((c = *wp++) != 0)
				tputC(c, shf);
			break;
		  case CSUBST:
			if (*wp++ == '}')
				tputc('}', shf);
			break;
#ifdef KSH
		  case OPAT:
			tputc(*wp++, shf);
			tputc('(', shf);
			break;
		  case SPAT:
			tputc('|', shf);
			break;
		  case CPAT:
			tputc(')', shf);
			break;
#endif /* KSH */
		}
