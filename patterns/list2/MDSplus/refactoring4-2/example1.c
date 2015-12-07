#ifdef _RECURSIVE_COMPRESS
while (status == MdsCOMPRESSIBLE)
#else
  if (status & 1)
#endif
  {
    status = MdsGet1Dx(&work.l_length, &dsc_dtype, out_ptr, NULL);
    if (status & 1) {
#ifdef _RECURSIVE_COMPRESS
      int orig_len = work.l_length;
#endif
      _MOVC3(work.l_length, work.pointer, out_ptr->pointer);
      status =
	  compress(cimage_ptr, centry_ptr, (char *)out_ptr->pointer - (char *)work.pointer,
		   work.pointer);
      if (status & 1)
	status = MdsCopyDxXd(work.pointer, out_ptr);
      MdsFree1Dx(&work, NULL);
#ifdef _RECURSIVE_COMPRESS
      if ((status == MdsCOMPRESSIBLE) && (orig_len / 2 > out_ptr->l_length)) {
	work = *out_ptr;
	out_ptr->pointer = 0;
	out_ptr->l_length = 0;
      } else
	status = 1;
#endif
    }
  }
