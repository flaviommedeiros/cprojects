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
