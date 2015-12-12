switch (optc) {
			  case 'R': /* fake BSD echo command */
				flags |= PO_PMINUSMINUS;
				flags &= ~PO_EXPAND;
				options = "ne";
				break;
			  case 'e':
				flags |= PO_EXPAND;
				break;
#ifdef OS2
			  case 'f':
				flags |= PO_FSLASH;
				break;
#endif
			  case 'n':
				flags &= ~PO_NL;
				break;
#ifdef KSH
			  case 'p':
				if ((fd = coproc_getfd(W_OK, &emsg)) < 0) {
					bi_errorf("-p: %s", emsg);
					return 1;
				}
				break;
#endif /* KSH */
			  case 'r':
				flags &= ~PO_EXPAND;
				break;
			  case 's':
				flags |= PO_HIST;
				break;
			  case 'u':
				if (!*(s = builtin_opt.optarg))
					fd = 0;
				else if ((fd = check_fd(s, W_OK, &emsg)) < 0) {
					bi_errorf("-u: %s: %s", s, emsg);
					return 1;
				}
				break;
			  case '?':
				return 1;
			}
