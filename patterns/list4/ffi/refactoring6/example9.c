if (i < fp_slot_max
	      && (arg_types[i]->type == FFI_TYPE_FLOAT
		  || arg_types[i]->type == FFI_TYPE_DOUBLE
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
		  || arg_types[i]->type == FFI_TYPE_LONGDOUBLE
#endif
		  ))
	    avalue[i] = ((char *) &fpr[argn]) - arg_types[i]->size;
	  else
	    avalue[i] = ((char *) &gpr[argn]) - arg_types[i]->size;
