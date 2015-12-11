#ifdef PNG_MAX_MALLOC_64K
if (size > (png_uint_32)65536L)
   {
#ifndef PNG_USER_MEM_SUPPORTED
      if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
         png_error(png_ptr, "Cannot Allocate > 64K");
      else
#endif
         return NULL;
   }
