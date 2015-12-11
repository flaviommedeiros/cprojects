if ((*p_arg)->type == FFI_TYPE_STRUCT
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
	      || (*p_arg)->type == FFI_TYPE_LONGDOUBLE
#endif
	      )
	    {
	      *(unsigned int *) argp = (unsigned long)(* p_argv);
	      z = sizeof(int);
	    }
	  else
	    {
	      z = (*p_arg)->size;
	      if (z < sizeof(int))
		{
		  z = sizeof(int);
		  switch ((*p_arg)->type)
		    {
		    case FFI_TYPE_SINT8:
		      *(signed int *) argp = *(SINT8 *)(* p_argv);
		      break;
		      
		    case FFI_TYPE_UINT8:
		      *(unsigned int *) argp = *(UINT8 *)(* p_argv);
		      break;
		      
		    case FFI_TYPE_SINT16:
		      *(signed int *) argp = *(SINT16 *)(* p_argv);
		      break;
		      
		    case FFI_TYPE_UINT16:
		      *(unsigned int *) argp = *(UINT16 *)(* p_argv);
		      break;

		    default:
		      FFI_ASSERT(0);
		    }
		}
	      else
		{
		  memcpy(argp, *p_argv, z);
		}
	    }
