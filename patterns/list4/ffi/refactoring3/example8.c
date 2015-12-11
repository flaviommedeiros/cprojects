switch (type)
	{
	case FFI_TYPE_SINT8:
	  *(SINT32 *)(stack - slot) = *(SINT8 *)(*p_argv);
	  break;

	case FFI_TYPE_UINT8:
	  *(UINT32 *)(stack - slot) = *(UINT8 *)(*p_argv);
	  break;

	case FFI_TYPE_SINT16:
	  *(SINT32 *)(stack - slot) = *(SINT16 *)(*p_argv);
	  break;

	case FFI_TYPE_UINT16:
	  *(UINT32 *)(stack - slot) = *(UINT16 *)(*p_argv);
	  break;

	case FFI_TYPE_UINT32:
	case FFI_TYPE_SINT32:
	case FFI_TYPE_POINTER:
	  debug(3, "Storing UINT32 %u in slot %u\n", *(UINT32 *)(*p_argv),
		slot);
	  *(UINT32 *)(stack - slot) = *(UINT32 *)(*p_argv);
	  break;

	case FFI_TYPE_UINT64:
	case FFI_TYPE_SINT64:
	  /* Align slot for 64-bit type.  */
	  slot += (slot & 1) ? 1 : 2;
	  *(UINT64 *)(stack - slot) = *(UINT64 *)(*p_argv);
	  break;

	case FFI_TYPE_FLOAT:
	  /* First 4 args go in fr4L - fr7L.  */
	  debug(3, "Storing UINT32(float) in slot %u\n", slot);
	  *(UINT32 *)(stack - slot) = *(UINT32 *)(*p_argv);
	  switch (slot - FIRST_ARG_SLOT)
	    {
	    /* First 4 args go in fr4L - fr7L.  */
	    case 0: fldw(stack - slot, fr4); break;
	    case 1: fldw(stack - slot, fr5); break;
	    case 2: fldw(stack - slot, fr6); break;
	    case 3: fldw(stack - slot, fr7); break;
	    }
	  break;

	case FFI_TYPE_DOUBLE:
	  /* Align slot for 64-bit type.  */
	  slot += (slot & 1) ? 1 : 2;
	  debug(3, "Storing UINT64(double) at slot %u\n", slot);
	  *(UINT64 *)(stack - slot) = *(UINT64 *)(*p_argv);
	  switch (slot - FIRST_ARG_SLOT)
	    {
	      /* First 2 args go in fr5, fr7.  */
	      case 1: fldd(stack - slot, fr5); break;
	      case 3: fldd(stack - slot, fr7); break;
	    }
	  break;

#ifdef PA_HPUX
	case FFI_TYPE_LONGDOUBLE:
	  /* Long doubles are passed in the same manner as structures
	     larger than 8 bytes.  */
	  *(UINT32 *)(stack - slot) = (UINT32)(*p_argv);
	  break;
#endif

	case FFI_TYPE_STRUCT:

	  /* Structs smaller or equal than 4 bytes are passed in one
	     register. Structs smaller or equal 8 bytes are passed in two
	     registers. Larger structures are passed by pointer.  */

	  len = (*p_arg)->size;
	  if (len <= 4)
	    {
	      dest_cpy = (char *)(stack - slot) + 4 - len;
	      memcpy(dest_cpy, (char *)*p_argv, len);
	    }
	  else if (len <= 8)
	    {
	      slot += (slot & 1) ? 1 : 2;
	      dest_cpy = (char *)(stack - slot) + 8 - len;
	      memcpy(dest_cpy, (char *)*p_argv, len);
	    }
	  else
	    *(UINT32 *)(stack - slot) = (UINT32)(*p_argv);
	  break;

	default:
	  FFI_ASSERT(0);
	}
