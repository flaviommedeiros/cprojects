switch (cif->abi) 
    {
#ifdef X86_WIN64
    case FFI_WIN64:
      {
        // Make copies of all struct arguments
        // NOTE: not sure if responsibility should be here or in caller
        unsigned int i;
        for (i=0; i < cif->nargs;i++) {
          size_t size = cif->arg_types[i]->size;
          if ((cif->arg_types[i]->type == FFI_TYPE_STRUCT
               && (size != 1 && size != 2 && size != 4 && size != 8))
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
              || cif->arg_types[i]->type == FFI_TYPE_LONGDOUBLE
#endif
              )
            {
              void *local = alloca(size);
              memcpy(local, avalue[i], size);
              avalue[i] = local;
            }
        }
        ffi_call_win64(ffi_prep_args, &ecif, cif->bytes,
                       cif->flags, ecif.rvalue, fn);
      }
      break;
#elif defined(X86_WIN32)
    case FFI_SYSV:
    case FFI_STDCALL:
      ffi_call_win32(ffi_prep_args, &ecif, cif->bytes, cif->flags,
                     ecif.rvalue, fn);
      break;
#else
    case FFI_SYSV:
      ffi_call_SYSV(ffi_prep_args, &ecif, cif->bytes, cif->flags, ecif.rvalue,
                    fn);
      break;
#endif
    default:
      FFI_ASSERT(0);
      break;
    }
