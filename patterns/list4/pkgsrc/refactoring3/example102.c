switch ((c = *wp++)) {
		  case EOS:
			return shf_sclose(&shf); /* null terminates */
		  case CHAR:
		  case QCHAR:
			shf_putchar(*wp++, &shf);
			break;
		  case COMSUB:
			shf_putchar('$', &shf);
			shf_putchar('(', &shf);
			while (*wp != 0)
				shf_putchar(*wp++, &shf);
			shf_putchar(')', &shf);
			break;
		  case EXPRSUB:
			shf_putchar('$', &shf);
			shf_putchar('(', &shf);
			shf_putchar('(', &shf);
			while (*wp != 0)
				shf_putchar(*wp++, &shf);
			shf_putchar(')', &shf);
			shf_putchar(')', &shf);
			break;
		  case OQUOTE:
			break;
		  case CQUOTE:
			break;
		  case OSUBST:
			shf_putchar('$', &shf);
			if (*wp++ == '{')
			    shf_putchar('{', &shf);
			while ((c = *wp++) != 0)
				shf_putchar(c, &shf);
			break;
		  case CSUBST:
			if (*wp++ == '}')
				shf_putchar('}', &shf);
			break;
#ifdef KSH
		  case OPAT:
			shf_putchar(*wp++, &shf);
			shf_putchar('(', &shf);
			break;
		  case SPAT:
			shf_putchar('|', &shf);
			break;
		  case CPAT:
			shf_putchar(')', &shf);
			break;
#endif /* KSH */
		}
