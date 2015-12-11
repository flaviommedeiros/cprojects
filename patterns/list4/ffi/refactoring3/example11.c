switch (type)
	{
	case FFI_TYPE_SINT8:
	case FFI_TYPE_UINT8:
	case FFI_TYPE_SINT16:
	case FFI_TYPE_UINT16:
	case FFI_TYPE_SINT32:
	case FFI_TYPE_UINT32:
	case FFI_TYPE_POINTER:
	  avalue[i] = (char *)(stack - slot) + sizeof(UINT32) - (*p_arg)->size;
	  break;

	case FFI_TYPE_SINT64:
	case FFI_TYPE_UINT64:
	  slot += (slot & 1) ? 1 : 2;
	  avalue[i] = (void *)(stack - slot);
	  break;

	case FFI_TYPE_FLOAT:
#ifdef PA_LINUX
	  /* The closure call is indirect.  In Linux, floating point
	     arguments in indirect calls with a prototype are passed
	     in the floating point registers instead of the general
	     registers.  So, we need to replace what was previously
	     stored in the current slot with the value in the
	     corresponding floating point register.  */
	  switch (slot - FIRST_ARG_SLOT)
	    {
	    case 0: fstw(fr4, (void *)(stack - slot)); break;
	    case 1: fstw(fr5, (void *)(stack - slot)); break;
	    case 2: fstw(fr6, (void *)(stack - slot)); break;
	    case 3: fstw(fr7, (void *)(stack - slot)); break;
	    }
#endif
	  avalue[i] = (void *)(stack - slot);
	  break;

	case FFI_TYPE_DOUBLE:
	  slot += (slot & 1) ? 1 : 2;
#ifdef PA_LINUX
	  /* See previous comment for FFI_TYPE_FLOAT.  */
	  switch (slot - FIRST_ARG_SLOT)
	    {
	    case 1: fstd(fr5, (void *)(stack - slot)); break;
	    case 3: fstd(fr7, (void *)(stack - slot)); break;
	    }
#endif
	  avalue[i] = (void *)(stack - slot);
	  break;

#ifdef PA_HPUX
	case FFI_TYPE_LONGDOUBLE:
	  /* Long doubles are treated like a big structure.  */
	  avalue[i] = (void *) *(stack - slot);
	  break;
#endif

	case FFI_TYPE_STRUCT:
	  /* Structs smaller or equal than 4 bytes are passed in one
	     register. Structs smaller or equal 8 bytes are passed in two
	     registers. Larger structures are passed by pointer.  */
	  if((*p_arg)->size <= 4)
	    {
	      avalue[i] = (void *)(stack - slot) + sizeof(UINT32) -
		(*p_arg)->size;
	    }
	  else if ((*p_arg)->size <= 8)
	    {
	      slot += (slot & 1) ? 1 : 2;
	      avalue[i] = (void *)(stack - slot) + sizeof(UINT64) -
		(*p_arg)->size;
	    }
	  else
	    avalue[i] = (void *) *(stack - slot);
	  break;

	default:
	  FFI_ASSERT(0);
	}
