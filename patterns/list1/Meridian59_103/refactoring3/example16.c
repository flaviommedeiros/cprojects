switch (*p1++)
		  {
		  case Cend:
		    abort();  /* we certainly shouldn't get this inside loop */
		    /*NOTREACHED*/
		  case Cbol:
		  case Ceol:
		  case Canychar:
		  case Cbegbuf:
		  case Cendbuf:
		  case Cwordbeg:
		  case Cwordend:
		  case Cwordbound:
		  case Cnotwordbound:
#ifdef EDH
		  case Cwordleft:
		  case Cwordright:
		  case Cnotwordleft:
		  case Cnotwordright:
#endif // EDH
		    break;
		  case Cset:
		    p1 += 256/8;
		    break;
		  case Cexact:
		  case Cstart_memory:
		  case Cend_memory:
		  case Cmatch_memory:
		  case Csyntaxspec:
		  case Cnotsyntaxspec:
		    p1++;
		    break;
		  case Cjump:
		  case Cstar_jump:
		  case Cfailure_jump:
		  case Cupdate_failure_jump:
		  case Cdummy_failure_jump:
		    goto make_normal_jump;
		  default:
		    printf("regexpr.c: processing star_jump: unknown op %d\n", p1[-1]);
		    break;
		  }
