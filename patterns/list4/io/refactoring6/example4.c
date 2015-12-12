if (cif->rtype->type == FFI_TYPE_STRUCT
#ifdef SPARC
      && (cif->abi != FFI_V9 || cif->rtype->size > 32)
#endif
     )
    bytes = STACK_ARG_SIZE(sizeof(void*));
