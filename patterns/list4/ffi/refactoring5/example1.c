#ifdef X86_WIN64
if ((*p_arg)->size > sizeof(ffi_arg)
          || ((*p_arg)->type == FFI_TYPE_STRUCT
              && ((*p_arg)->size != 1 && (*p_arg)->size != 2
                  && (*p_arg)->size != 4 && (*p_arg)->size != 8)))
        {
          z = sizeof(void *);
          *p_argv = *(void **)argp;
        }
      else
#endif
        {
          z = (*p_arg)->size;
          
          /* because we're little endian, this is what it turns into.   */
          
          *p_argv = (void*) argp;
        }
