#if (PNG_LIBPNG_VER < 10500)
if (setjmp(png_ptr->jmpbuf))
#else
   if (setjmp(*png_set_longjmp_fn(png_ptr, longjmp, sizeof (jmp_buf))))
#endif
   {
      png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
return(false);
   }
