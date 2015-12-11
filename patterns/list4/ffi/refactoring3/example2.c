switch (cif->rtype->type)
    {

#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
    case FFI_TYPE_LONGDOUBLE:
      flags |= FLAG_RETURNS_128BITS;
      flags |= FLAG_RETURNS_FP;
      break;
#endif

    case FFI_TYPE_DOUBLE:
      flags |= FLAG_RETURNS_64BITS;
      /* Fall through.  */
    case FFI_TYPE_FLOAT:
      flags |= FLAG_RETURNS_FP;
      break;

    case FFI_TYPE_UINT64:
    case FFI_TYPE_SINT64:
#ifdef POWERPC64
    case FFI_TYPE_POINTER:
#endif
      flags |= FLAG_RETURNS_64BITS;
      break;

    case FFI_TYPE_STRUCT:
#if defined(POWERPC_DARWIN64)
      {
	/* Can we fit the struct into regs?  */
	if (darwin64_struct_ret_by_value_p (cif->rtype))
	  {
	    unsigned nfpr = 0;
	    flags |= FLAG_RETURNS_STRUCT;
	    if (cif->rtype->size != 16)
	      darwin64_scan_struct_for_floats (cif->rtype, &nfpr) ;
	    else
	      flags |= FLAG_RETURNS_128BITS;
	    /* Will be 0 for 16byte struct.  */
	    if (nfpr)
	      flags |= FLAG_RETURNS_FP;
	  }
	else /* By ref. */
	  {
	    flags |= FLAG_RETVAL_REFERENCE;
	    flags |= FLAG_RETURNS_NOTHING;
	    intarg_count++;
	  }
      }
#elif defined(DARWIN_PPC)
      if (cif->rtype->size <= 4)
	flags |= FLAG_RETURNS_STRUCT;
      else /* else by reference.  */
	{
	  flags |= FLAG_RETVAL_REFERENCE;
	  flags |= FLAG_RETURNS_NOTHING;
	  intarg_count++;
	}
#else /* assume we pass by ref.  */
      flags |= FLAG_RETVAL_REFERENCE;
      flags |= FLAG_RETURNS_NOTHING;
      intarg_count++;
#endif
      break;
    case FFI_TYPE_VOID:
      flags |= FLAG_RETURNS_NOTHING;
      break;

    default:
      /* Returns 32-bit integer, or similar.  Nothing to do here.  */
      break;
    }
