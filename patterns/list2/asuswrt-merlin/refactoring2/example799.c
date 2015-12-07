#ifdef NO_XMALLOC
if (result != NULL)
#endif
	    {
	      memcpy (result, curr_prefix, curr_prefix_len);
	      strcpy (result + curr_prefix_len, pathname_tail);
	      return result;
	    }
