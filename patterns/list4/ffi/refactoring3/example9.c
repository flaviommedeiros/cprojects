switch (type)
	{
	case FFI_TYPE_DOUBLE:
	case FFI_TYPE_UINT64:
	case FFI_TYPE_SINT64:
	  z += 2 + (z & 1); /* must start on even regs, so we may waste one */
	  break;

#ifdef PA_HPUX
	case FFI_TYPE_LONGDOUBLE:
#endif
	case FFI_TYPE_STRUCT:
	  z += 1; /* pass by ptr, callee will copy */
	  break;

	default: /* <= 32-bit values */
	  z++;
	}
