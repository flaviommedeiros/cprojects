#ifdef PNG_USER_LIMITS_SUPPORTED
if (setjmp(tmp_jmpbuf))
#else
   if (setjmp(png_jmpbuf(png_ptr))) /* Sets longjmp to match setjmp */
#endif
      PNG_ABORT();
