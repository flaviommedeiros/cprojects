switch (type) 
	{
	  /* The first MAX_FPRARGS floating point arguments
	     go in FPRs, the rest overflow to the stack.  */

	  case FFI_TYPE_DOUBLE:
	    if (n_fpr < MAX_FPRARGS)
	      n_fpr++;
	    else
	      n_ov += sizeof (double) / sizeof (long);
	    break;
	
	  case FFI_TYPE_FLOAT:
	    if (n_fpr < MAX_FPRARGS)
	      n_fpr++;
	    else
	      n_ov++;
	    break;

	  /* On 31-bit machines, 64-bit integers are passed in GPR pairs,
	     if one is still available, or else on the stack.  If only one
	     register is free, skip the register (it won't be used for any 
	     subsequent argument either).  */
	      
#ifndef __s390x__
	  case FFI_TYPE_UINT64:
	  case FFI_TYPE_SINT64:
	    if (n_gpr == MAX_GPRARGS-1)
	      n_gpr = MAX_GPRARGS;
	    if (n_gpr < MAX_GPRARGS)
	      n_gpr += 2;
	    else
	      n_ov += 2;
	    break;
#endif

	  /* Everything else is passed in GPRs (until MAX_GPRARGS
	     have been used) or overflows to the stack.  */

	  default: 
	    if (n_gpr < MAX_GPRARGS)
	      n_gpr++;
	    else
	      n_ov++;
	    break;
        }
