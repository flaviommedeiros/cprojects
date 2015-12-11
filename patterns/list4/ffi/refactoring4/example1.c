#ifdef FFI_MIPS_N32
if ( ecif->cif->rstruct_flag != 0 )
#else
  if ( ecif->cif->rtype->type == FFI_TYPE_STRUCT )
#endif  
    {
      *(ffi_arg *) argp = (ffi_arg) ecif->rvalue;
      argp += sizeof(ffi_arg);
      FIX_ARGP;
    }
