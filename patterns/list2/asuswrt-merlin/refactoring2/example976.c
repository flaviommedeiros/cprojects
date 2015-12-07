#ifdef NO_XMALLOC
if (result != NULL)
#endif
            {
              strcpy (result, curr_prefix);
              return result;
            }
