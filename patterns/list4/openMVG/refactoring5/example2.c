#  ifdef PNG_WRITE_SUPPORTED
if (png_ptr->mode & PNG_IS_READ_STRUCT)
#  endif
   {
#     ifdef PNG_SEQUENTIAL_READ_SUPPORTED
         return png_ptr->IDAT_read_size;
#     else
         return PNG_IDAT_READ_SIZE;
#     endif
   }

#  ifdef PNG_WRITE_SUPPORTED
      else
         return png_ptr->zbuffer_size;
