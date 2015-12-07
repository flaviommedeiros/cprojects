#ifdef ENABLE_CACHING
if (info->cached_indexentry != NULL
      && offset >= info->cached_offset
      && offset < (info->cached_indexentry + 1)->val)
    {
      stab = info->cached_stab;
      indexentry = info->cached_indexentry;
      file_name = info->cached_file_name;
    }
  else
#endif
    {
      long low, high;
      long mid = -1;

      /* Cache non-existent or invalid.  Do binary search on
         indextable.  */
      indexentry = NULL;

      low = 0;
      high = info->indextablesize - 1;
      while (low != high)
	{
	  mid = (high + low) / 2;
	  if (offset >= info->indextable[mid].val
	      && offset < info->indextable[mid + 1].val)
	    {
	      indexentry = &info->indextable[mid];
	      break;
	    }

	  if (info->indextable[mid].val > offset)
	    high = mid;
	  else
	    low = mid + 1;
	}

      if (indexentry == NULL)
	return TRUE;

      stab = indexentry->stab + STABSIZE;
      file_name = indexentry->file_name;
    }
