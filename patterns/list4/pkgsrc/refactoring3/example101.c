switch (*wp++) {
		  case EOS:
			return (char *) __UNCONST(wp);
		  case CHAR:
		  case QCHAR:
			wp++;
			break;
		  case COMSUB:
		  case EXPRSUB:
			while (*wp++ != 0)
				;
			break;
		  case OQUOTE:
		  case CQUOTE:
			break;
		  case OSUBST:
			nest++;
			while (*wp++ != '\0')
				;
			break;
		  case CSUBST:
			wp++;
			if (c == CSUBST && nest == 0)
				return (char *) __UNCONST(wp);
			nest--;
			break;
#ifdef KSH
		  case OPAT:
			nest++;
			wp++;
			break;
		  case SPAT:
		  case CPAT:
			if (c == wp[-1] && nest == 0)
				return (char *) __UNCONST(wp);
			if (wp[-1] == CPAT)
				nest--;
			break;
#endif /* KSH */
		  default:
			internal_errorf(0,
				"wdscan: unknown char 0x%x (carrying on)",
				wp[-1]);
		}
