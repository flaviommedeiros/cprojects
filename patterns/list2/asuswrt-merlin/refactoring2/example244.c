#ifdef NO_XMALLOC
if (memory != NULL)
#endif
        {
          memcpy (memory, orig_prefix_arg, orig_prefix_len + 1);
          orig_prefix = memory;
          memory += orig_prefix_len + 1;
          memcpy (memory, curr_prefix_arg, curr_prefix_len + 1);
          curr_prefix = memory;
          return;
        }
