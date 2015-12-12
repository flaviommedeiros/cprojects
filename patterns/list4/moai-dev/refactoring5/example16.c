#ifdef PNG_MAX_MALLOC_64K
if (size > (png_uint_32)65536L)
   {
      png_warning(png_ptr, "Cannot Allocate > 64K");
      ret = NULL;
   }
   else
#endif

   if (size != (size_t)size)
      ret = NULL;
   else if (size == (png_uint_32)65536L)
   {
      if (png_ptr->offset_table == NULL)
      {
         /* Try to see if we need to do any of this fancy stuff */
         ret = farmalloc(size);
         if (ret == NULL || ((png_size_t)ret & 0xffff))
         {
            int num_blocks;
            png_uint_32 total_size;
            png_bytep table;
            int i;
            png_byte huge * hptr;

            if (ret != NULL)
            {
               farfree(ret);
               ret = NULL;
            }

            if (png_ptr->zlib_window_bits > 14)
               num_blocks = (int)(1 << (png_ptr->zlib_window_bits - 14));
            else
               num_blocks = 1;
            if (png_ptr->zlib_mem_level >= 7)
               num_blocks += (int)(1 << (png_ptr->zlib_mem_level - 7));
            else
               num_blocks++;

            total_size = ((png_uint_32)65536L) * (png_uint_32)num_blocks+16;

            table = farmalloc(total_size);

            if (table == NULL)
            {
#ifndef PNG_USER_MEM_SUPPORTED
               if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
                  png_error(png_ptr, "Out Of Memory"); /* Note "O" and "M" */
               else
                  png_warning(png_ptr, "Out Of Memory");
#endif
               return (NULL);
            }

            if ((png_size_t)table & 0xfff0)
            {
#ifndef PNG_USER_MEM_SUPPORTED
               if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
                  png_error(png_ptr,
                    "Farmalloc didn't return normalized pointer");
               else
                  png_warning(png_ptr,
                    "Farmalloc didn't return normalized pointer");
#endif
               return (NULL);
            }

            png_ptr->offset_table = table;
            png_ptr->offset_table_ptr = farmalloc(num_blocks *
               png_sizeof(png_bytep));

            if (png_ptr->offset_table_ptr == NULL)
            {
#ifndef PNG_USER_MEM_SUPPORTED
               if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
                  png_error(png_ptr, "Out Of memory"); /* Note "O" and "M" */
               else
                  png_warning(png_ptr, "Out Of memory");
#endif
               return (NULL);
            }

            hptr = (png_byte huge *)table;
            if ((png_size_t)hptr & 0xf)
            {
               hptr = (png_byte huge *)((long)(hptr) & 0xfffffff0L);
               hptr = hptr + 16L;  /* "hptr += 16L" fails on Turbo C++ 3.0 */
            }
            for (i = 0; i < num_blocks; i++)
            {
               png_ptr->offset_table_ptr[i] = (png_bytep)hptr;
               hptr = hptr + (png_uint_32)65536L;  /* "+=" fails on TC++3.0 */
            }

            png_ptr->offset_table_number = num_blocks;
            png_ptr->offset_table_count = 0;
            png_ptr->offset_table_count_free = 0;
         }
      }

      if (png_ptr->offset_table_count >= png_ptr->offset_table_number)
      {
#ifndef PNG_USER_MEM_SUPPORTED
         if ((png_ptr->flags&PNG_FLAG_MALLOC_NULL_MEM_OK) == 0)
            png_error(png_ptr, "Out of Memory"); /* Note "o" and "M" */
         else
            png_warning(png_ptr, "Out of Memory");
#endif
         return (NULL);
      }

      ret = png_ptr->offset_table_ptr[png_ptr->offset_table_count++];
   }
   else
      ret = farmalloc(size);
