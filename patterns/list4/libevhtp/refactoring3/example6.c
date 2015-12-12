switch (c) {
	  case ':':
	  case ')':
	  break;

	  case '-':  neg = 1; break;
	  case 'x':  ONOFF(option, ONIG_OPTION_EXTEND,     neg); break;
	  case 'i':  ONOFF(option, ONIG_OPTION_IGNORECASE, neg); break;
	  case 's':
	    if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_PERL)) {
	      ONOFF(option, ONIG_OPTION_MULTILINE,  neg);
	    }
	    else
	      return ONIGERR_UNDEFINED_GROUP_OPTION;
	    break;

	  case 'm':
	    if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_PERL)) {
	      ONOFF(option, ONIG_OPTION_SINGLELINE, (neg == 0 ? 1 : 0));
	    }
	    else if (IS_SYNTAX_OP2(env->syntax, ONIG_SYN_OP2_OPTION_RUBY)) {
	      ONOFF(option, ONIG_OPTION_MULTILINE,  neg);
	    }
	    else
	      return ONIGERR_UNDEFINED_GROUP_OPTION;
	    break;
#ifdef USE_POSIXLINE_OPTION
	  case 'p':
	    ONOFF(option, ONIG_OPTION_MULTILINE|ONIG_OPTION_SINGLELINE, neg);
	    break;
#endif
	  default:
	    return ONIGERR_UNDEFINED_GROUP_OPTION;
	  }
