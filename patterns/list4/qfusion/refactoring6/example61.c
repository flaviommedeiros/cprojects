if (
#ifdef PNG_USELESS_TESTS_SUPPORTED
       row != NULL && row_info != NULL &&
#endif
       (row_info->color_type & PNG_COLOR_MASK_COLOR))
   {
      png_uint_32 row_width = row_info->width;
      if (row_info->bit_depth == 8)
      {
         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 3)
            {
               png_byte save = *rp;
               *rp = *(rp + 2);
               *(rp + 2) = save;
            }
         }
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 4)
            {
               png_byte save = *rp;
               *rp = *(rp + 2);
               *(rp + 2) = save;
            }
         }
      }
      else if (row_info->bit_depth == 16)
      {
         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 6)
            {
               png_byte save = *rp;
               *rp = *(rp + 4);
               *(rp + 4) = save;
               save = *(rp + 1);
               *(rp + 1) = *(rp + 5);
               *(rp + 5) = save;
            }
         }
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
         {
            png_bytep rp;
            png_uint_32 i;

            for (i = 0, rp = row; i < row_width; i++, rp += 8)
            {
               png_byte save = *rp;
               *rp = *(rp + 4);
               *(rp + 4) = save;
               save = *(rp + 1);
               *(rp + 1) = *(rp + 5);
               *(rp + 5) = save;
            }
         }
      }
   }
