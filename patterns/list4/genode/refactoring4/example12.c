#if !defined(PNG_1_0_X)
if (setjmp(jmpbuf))
#else
   if (setjmp(png_ptr->jmpbuf))
#endif
   {
      png_free(png_ptr, png_ptr->zbuf);
      png_ptr->zbuf=NULL;
      png_destroy_struct(png_ptr);
      return (NULL);
   }
