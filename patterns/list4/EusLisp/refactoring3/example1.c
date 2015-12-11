switch(av[1][i])
	    {
#ifndef VMS  /* These options are useful only with ctags,
		and VMS can't input them, so just omit them.  */
	    case 'B':
	      searchar='?';
	      eflag = 0;
	      break;
	    case 'F':
	      searchar='/';
	      eflag = 0;
	      break;
#endif
	    case 'a':
	      aflag++;
	      break;
	    case 'e':
	      eflag++;
	      break;
	    case 'f':
	      if (fflag > 0)
		{
		  fprintf(stderr,
			  "%s: -f flag may only be given once\n", progname);
		  goto usage;
		}
	      fflag++, ac--; av++;
	      if (ac <= 1 || av[1][0] == '\0')
		{
		  fprintf(stderr,
			  "%s: -f flag must be followed by a filename\n",
			  progname);
		  goto usage;
		}
	      outfile = av[1];
	      goto end_loop;
	    case 't':
	      tflag++;
	      break;
#ifndef VMS
	    case 'u':
	      uflag++;
	      eflag = 0;
	      break;
#endif
	    case 'w':
	      wflag++;
	      break;
	    case 'v':
	      vflag++;
	      xflag++;
	      eflag = 0;
	      break;
	    case 'x':
	      xflag++;
	      eflag = 0;
	      break;
	    default:
	      goto usage;
	    }
