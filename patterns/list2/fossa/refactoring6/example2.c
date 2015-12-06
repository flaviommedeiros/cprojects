if( pMem->r==(double)pMem->u.i
   && pMem->u.i>SMALLEST_INT64
#if defined(__i486__) || defined(__x86_64__)
   && ALWAYS(pMem->u.i<LARGEST_INT64)
#else
   && pMem->u.i<LARGEST_INT64
#endif
  ){
    pMem->flags |= MEM_Int;
  }
