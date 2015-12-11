if (rvalue == NULL
#ifdef PA_HPUX
      && (cif->rtype->type == FFI_TYPE_STRUCT
	  || cif->rtype->type == FFI_TYPE_LONGDOUBLE))
#else
      && cif->rtype->type == FFI_TYPE_STRUCT
