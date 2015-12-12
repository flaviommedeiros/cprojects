switch (specType) {
	    case Suffixes:
		Suff_ClearSuffixes();
		break;
	    case Precious:
		allPrecious = TRUE;
		break;
	    case Ignore:
		ignoreErrors = TRUE;
		break;
	    case Silent:
		beSilent = TRUE;
		break;
	    case ExPath:
		Lst_ForEach(paths, ParseClearPath, NULL);
		Dir_SetPATH();
		break;
#ifdef POSIX
            case Posix:
                Var_Set("%POSIX", "1003.2", VAR_GLOBAL, 0);
                break;
#endif
	    default:
		break;
	}
