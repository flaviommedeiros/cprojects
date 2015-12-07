#ifdef __CYGWIN__
if (len > 1 || *expansion != '/' || *string != '/')
#endif
	{
	  if ((result_index + len + 1) > result_size)
	    result = (char *)xrealloc (result, 1 + (result_size += (len + 20)));

	  strcpy (result + result_index, expansion);
	  result_index += len;
	}
