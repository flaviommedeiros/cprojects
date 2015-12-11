if (cif->flags == FFI_TYPE_STRUCT
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE  
      || cif->flags == FFI_TYPE_LONGDOUBLE
#endif
     )
    rvalue = (void *) gpr[0];
