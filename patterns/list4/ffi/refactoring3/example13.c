switch (cif->abi) 
    {
#ifdef FFI_MIPS_O32
    case FFI_O32:
    case FFI_O32_SOFT_FLOAT:
      ffi_call_O32(ffi_prep_args, &ecif, cif->bytes, 
		   cif->flags, ecif.rvalue, fn);
      break;
#endif

#ifdef FFI_MIPS_N32
    case FFI_N32:
    case FFI_N32_SOFT_FLOAT:
    case FFI_N64:
    case FFI_N64_SOFT_FLOAT:
      {
        int copy_rvalue = 0;
	int copy_offset = 0;
        char *rvalue_copy = ecif.rvalue;
        if (cif->rtype->type == FFI_TYPE_STRUCT && cif->rtype->size < 16)
          {
            /* For structures smaller than 16 bytes we clobber memory
               in 8 byte increments.  Make a copy so we don't clobber
               the callers memory outside of the struct bounds.  */
            rvalue_copy = alloca(16);
            copy_rvalue = 1;
          }
	else if (cif->rtype->type == FFI_TYPE_FLOAT
		 && (cif->abi == FFI_N64_SOFT_FLOAT
		     || cif->abi == FFI_N32_SOFT_FLOAT))
	  {
	    rvalue_copy = alloca (8);
	    copy_rvalue = 1;
#if defined(__MIPSEB__) || defined(_MIPSEB)
	    copy_offset = 4;
#endif
	  }
        ffi_call_N32(ffi_prep_args, &ecif, cif->bytes,
                     cif->flags, rvalue_copy, fn);
        if (copy_rvalue)
          memcpy(ecif.rvalue, rvalue_copy + copy_offset, cif->rtype->size);
      }
      break;
#endif

    default:
      FFI_ASSERT(0);
      break;
    }
