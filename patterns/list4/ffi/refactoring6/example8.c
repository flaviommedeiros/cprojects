if (arg_types[i]->type == FFI_TYPE_STRUCT
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
	  || arg_types[i]->type == FFI_TYPE_LONGDOUBLE
#endif
         )
	{
	  /* Straight copy of invisible reference.  */
	  avalue[i] = (void *)gpr[argn++];
	}
      else if ((arg_types[i]->type == FFI_TYPE_DOUBLE
	       || arg_types[i]->type == FFI_TYPE_SINT64
	       || arg_types[i]->type == FFI_TYPE_UINT64)
	       /* gpr is 8-byte aligned.  */
	       && (argn % 2) != 0)
	{
	  /* Align on a 8-byte boundary.  */
	  scratch[0] = gpr[argn];
	  scratch[1] = gpr[argn+1];
	  avalue[i] = scratch;
	  scratch -= 2;
	  argn += 2;
	}
      else
	{
	  /* Always right-justify.  */
	  argn += ALIGN(arg_types[i]->size, FFI_SIZEOF_ARG) / FFI_SIZEOF_ARG;
	  avalue[i] = ((char *) &gpr[argn]) - arg_types[i]->size;
	}
