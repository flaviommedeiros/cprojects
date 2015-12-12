#ifdef SPARC
if (((*ptr)->type == FFI_TYPE_STRUCT
	   && ((*ptr)->size > 16 || cif->abi != FFI_V9))
	  || ((*ptr)->type == FFI_TYPE_LONGDOUBLE
	      && cif->abi != FFI_V9))
	bytes += sizeof(void*);
      else
#endif
	{
	  /* Add any padding if necessary */
	  if (((*ptr)->alignment - 1) & bytes)
	    bytes = ALIGN(bytes, (*ptr)->alignment);

	  bytes += STACK_ARG_SIZE((*ptr)->size);
	}
