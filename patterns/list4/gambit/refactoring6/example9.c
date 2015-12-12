if (WORDS_OCCUPIED > heap_size
#ifdef CALL_GC_FREQUENTLY
      || --___gc_calls_to_punt < 0
#endif
      )
    {
      ___BOOL overflow;

      words_nonmovable -= words;

      overflow = ___garbage_collect (___PSP words);

      words_nonmovable += words;

      alloc_stack_ptr = ___ps->fp; /* needed by 'WORDS_OCCUPIED' */
      alloc_heap_ptr  = ___ps->hp; /* needed by 'WORDS_OCCUPIED' */

      if (overflow || WORDS_OCCUPIED > heap_size)
        {
          words_nonmovable -= words;
          return ___FIX(___HEAP_OVERFLOW_ERR);
        }
    }
