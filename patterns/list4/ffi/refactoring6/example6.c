if (rvalue && (cif->rtype->type == FFI_TYPE_STRUCT
#if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
	  || cif->flags == FFI_TYPE_LONGDOUBLE
#endif
	  ))
	{
	  /* For v8, we need an "unimp" with size of returning struct */
	  /* behind "call", so we alloc some executable space for it. */
	  /* l7 is used, we need to make sure v8.S doesn't use %l7.   */
	  unsigned int *call_struct = NULL;
	  ffi_closure_alloc(32, &call_struct);
	  if (call_struct)
	    {
	      unsigned long f = (unsigned long)fn;
	      call_struct[0] = 0xae10001f;		 /* mov   %i7, %l7	 */
	      call_struct[1] = 0xbe10000f;		 /* mov   %o7, %i7	 */
	      call_struct[2] = 0x03000000 | f >> 10;     /* sethi %hi(fn), %g1	 */
	      call_struct[3] = 0x9fc06000 | (f & 0x3ff); /* jmp %g1+%lo(fn), %o7 */
	      call_struct[4] = 0x01000000;		 /* nop			 */
	      if (cif->rtype->size < 0x7f)
		call_struct[5] = cif->rtype->size;	 /* unimp		 */
	      else
		call_struct[5] = 0x01000000;	     	 /* nop			 */
	      call_struct[6] = 0x81c7e008;		 /* ret			 */
	      call_struct[7] = 0xbe100017;		 /* mov   %l7, %i7	 */
	      asm volatile ("iflush %0; iflush %0+8; iflush %0+16; iflush %0+24" : :
			    "r" (call_struct) : "memory");
	      /* SPARC v8 requires 5 instructions for flush to be visible */
	      asm volatile ("nop; nop; nop; nop; nop");
	      ffi_call_v8(ffi_prep_args_v8, &ecif, cif->bytes,
			  cif->flags, rvalue, call_struct);
	      ffi_closure_free(call_struct);
	    }
	  else
	    {
	      ffi_call_v8(ffi_prep_args_v8, &ecif, cif->bytes,
			  cif->flags, rvalue, fn);
	    }
	}
      else
	{
	  ffi_call_v8(ffi_prep_args_v8, &ecif, cif->bytes,
		      cif->flags, rvalue, fn);
	}
