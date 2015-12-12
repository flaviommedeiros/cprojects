#ifdef PNG_SET_USER_LIMITS_SUPPORTED
if (setjmp(jmpbuf))
#else
   if (setjmp(png_jmpbuf(png_ptr))) /* sets longjmp to match setjmp */
#endif
#ifdef USE_FAR_KEYWORD
   png_memcpy(png_jmpbuf(png_ptr), jmpbuf, png_sizeof(jmp_buf));
