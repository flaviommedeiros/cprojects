#if (PNG_LIBPNG_VER < 10500)
if (setjmp(png_ptr->jmpbuf))
#else
    if (setjmp(*png_set_longjmp_fn(png_ptr, longjmp, sizeof (jmp_buf))))
#endif
    {
      /* Free all of the memory associated with the png_ptr and info_ptr */
      png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
      if ( ret!=NULL ) {
	  GImageDestroy(ret);
	  free(row_pointers);
      }
      /* If we get here, we had a problem reading the file */
return( NULL );
    }
