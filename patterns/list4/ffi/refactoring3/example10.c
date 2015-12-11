switch (cif->rtype->type)
    {
    case FFI_TYPE_VOID:
    case FFI_TYPE_FLOAT:
    case FFI_TYPE_DOUBLE:
      cif->flags = (unsigned) cif->rtype->type;
      break;

#ifdef PA_HPUX
    case FFI_TYPE_LONGDOUBLE:
      /* Long doubles are treated like a structure.  */
      cif->flags = FFI_TYPE_STRUCT;
      break;
#endif

    case FFI_TYPE_STRUCT:
      /* For the return type we have to check the size of the structures.
	 If the size is smaller or equal 4 bytes, the result is given back
	 in one register. If the size is smaller or equal 8 bytes than we
	 return the result in two registers. But if the size is bigger than
	 8 bytes, we work with pointers.  */
      cif->flags = ffi_struct_type(cif->rtype);
      break;

    case FFI_TYPE_UINT64:
    case FFI_TYPE_SINT64:
      cif->flags = FFI_TYPE_UINT64;
      break;

    default:
      cif->flags = FFI_TYPE_INT;
      break;
    }
