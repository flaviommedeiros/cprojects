if (ecif->cif->flags == FFI_TYPE_STRUCT
#ifdef X86_WIN64
      && (ecif->cif->rtype->size != 1 && ecif->cif->rtype->size != 2
          && ecif->cif->rtype->size != 4 && ecif->cif->rtype->size != 8)
#endif
      )
    {
      *(void **) argp = ecif->rvalue;
      argp += sizeof(void*);
    }
