switch (optc) {
#ifdef KSH
		  case 'p':
			if ((fd = coproc_getfd(R_OK, &emsg)) < 0) {
				bi_errorf("-p: %s", emsg);
				return 1;
			}
			break;
#endif /* KSH */
		  case 'r':
			expandv = 0;
			break;
		  case 's':
			history = 1;
			break;
		  case 'u':
			if (!*(cp = builtin_opt.optarg))
				fd = 0;
			else if ((fd = check_fd(cp, R_OK, &emsg)) < 0) {
				bi_errorf("-u: %s: %s", cp, emsg);
				return 1;
			}
			break;
		  case '?':
			return 1;
		}
