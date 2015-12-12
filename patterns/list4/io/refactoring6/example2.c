if (z > sizeof(ffi_arg)
          || ((*p_arg)->type == FFI_TYPE_STRUCT
              && (z != 1 && z != 2 && z != 4 && z != 8))
#if FFI_TYPE_DOUBLE != FFI_TYPE_LONGDOUBLE
          || ((*p_arg)->type == FFI_TYPE_LONGDOUBLE)
#endif
          )
        {
          z = sizeof(ffi_arg);
          *(void **)argp = *p_argv;
        }
      else if ((*p_arg)->type == FFI_TYPE_FLOAT)
        {
          memcpy(argp, *p_argv, z);
        }
      else
#endif
      if (z < sizeof(ffi_arg))
        {
          z = sizeof(ffi_arg);
          switch ((*p_arg)->type)
            {
            case FFI_TYPE_SINT8:
              *(ffi_sarg *) argp = (ffi_sarg)*(SINT8 *)(* p_argv);
              break;

            case FFI_TYPE_UINT8:
              *(ffi_arg *) argp = (ffi_arg)*(UINT8 *)(* p_argv);
              break;

            case FFI_TYPE_SINT16:
              *(ffi_sarg *) argp = (ffi_sarg)*(SINT16 *)(* p_argv);
              break;

            case FFI_TYPE_UINT16:
              *(ffi_arg *) argp = (ffi_arg)*(UINT16 *)(* p_argv);
              break;

            case FFI_TYPE_SINT32:
              *(ffi_sarg *) argp = (ffi_sarg)*(SINT32 *)(* p_argv);
              break;

            case FFI_TYPE_UINT32:
              *(ffi_arg *) argp = (ffi_arg)*(UINT32 *)(* p_argv);
              break;

            case FFI_TYPE_STRUCT:
              *(ffi_arg *) argp = *(ffi_arg *)(* p_argv);
              break;

            default:
              FFI_ASSERT(0);
            }
        }
      else
        {
          memcpy(argp, *p_argv, z);
        }
