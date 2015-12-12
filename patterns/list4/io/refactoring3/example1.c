switch (cif->rtype->type)
    {
    case FFI_TYPE_VOID:
#if defined(X86) || defined (X86_WIN32) || defined(X86_FREEBSD) || defined(X86_DARWIN) || defined(X86_WIN64)
    case FFI_TYPE_UINT8:
    case FFI_TYPE_UINT16:
    case FFI_TYPE_SINT8:
    case FFI_TYPE_SINT16:
#endif
#ifdef X86_WIN64
    case FFI_TYPE_UINT32:
    case FFI_TYPE_SINT32:
#endif
    case FFI_TYPE_SINT64:
    case FFI_TYPE_FLOAT:
    case FFI_TYPE_DOUBLE:
#ifndef X86_WIN64
#if FFI_TYPE_DOUBLE != FFI_TYPE_LONGDOUBLE
    case FFI_TYPE_LONGDOUBLE:
#endif
#endif
      cif->flags = (unsigned) cif->rtype->type;
      break;

    case FFI_TYPE_UINT64:
#ifdef X86_WIN64
    case FFI_TYPE_POINTER:
#endif
      cif->flags = FFI_TYPE_SINT64;
      break;

    case FFI_TYPE_STRUCT:
#ifndef X86
      if (cif->rtype->size == 1)
        {
          cif->flags = FFI_TYPE_SMALL_STRUCT_1B; /* same as char size */
        }
      else if (cif->rtype->size == 2)
        {
          cif->flags = FFI_TYPE_SMALL_STRUCT_2B; /* same as short size */
        }
      else if (cif->rtype->size == 4)
        {
#ifdef X86_WIN64
          cif->flags = FFI_TYPE_SMALL_STRUCT_4B;
#else
          cif->flags = FFI_TYPE_INT; /* same as int type */
#endif
        }
      else if (cif->rtype->size == 8)
        {
          cif->flags = FFI_TYPE_SINT64; /* same as int64 type */
        }
      else
#endif
        {
          cif->flags = FFI_TYPE_STRUCT;
          // allocate space for return value pointer
          cif->bytes += ALIGN(sizeof(void*), FFI_SIZEOF_ARG);
        }
      break;

    default:
#ifdef X86_WIN64
      cif->flags = FFI_TYPE_SINT64;
      break;
    case FFI_TYPE_INT:
      cif->flags = FFI_TYPE_SINT32;
#else
      cif->flags = FFI_TYPE_INT;
#endif
      break;
    }
