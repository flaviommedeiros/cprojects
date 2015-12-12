#ifdef PNG_WRITE_SUPPORTED
if (setjmp(jmpbuf))
#else
   if (setjmp(png_jmpbuf(read_ptr)))
#endif
   {
      fprintf(STDERR, "%s -> %s: libpng read error\n", inname, outname);
      if (row_buf)
         png_free(read_ptr, row_buf);
      png_destroy_read_struct(&read_ptr, &read_info_ptr, &end_info_ptr);
#ifdef PNG_WRITE_SUPPORTED
      png_destroy_info_struct(write_ptr, &write_end_info_ptr);
      png_destroy_write_struct(&write_ptr, &write_info_ptr);
#endif
      FCLOSE(fpin);
      FCLOSE(fpout);
      return (1);
   }
