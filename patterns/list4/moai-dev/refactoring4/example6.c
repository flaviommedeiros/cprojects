#ifdef PNG_SET_USER_LIMITS_SUPPORTED
if (setjmp(jmpbuf))
#else
   if (setjmp(png_jmpbuf(png_ptr))) /* Sets longjmp to match setjmp */
#endif
      PNG_ABORT();
