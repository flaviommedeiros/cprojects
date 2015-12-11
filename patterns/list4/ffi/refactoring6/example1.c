if ((cif->rtype->type == FFI_TYPE_STRUCT
       && !((cif->abi == FFI_SYSV) && (size <= 8)))
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
      || (cif->rtype->type == FFI_TYPE_LONGDOUBLE
	  && cif->abi != FFI_LINUX && cif->abi != FFI_LINUX_SOFT_FLOAT)
#endif
      )
    {
      rvalue = (void *) *pgr;
      ng++;
      pgr++;
    }
