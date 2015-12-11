#ifdef PNG_USELESS_TESTS_SUPPORTED
if (row != NULL && row_info != NULL)
#endif
   {
      if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
      {
         /* This converts from ARGB to RGBA */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp, dp;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;
            for (i = 0, sp = dp = row; i < row_width; i++)
            {
               png_byte save = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = save;
            }
         }
         /* This converts from AARRGGBB to RRGGBBAA */
         else
         {
            png_bytep sp, dp;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            for (i = 0, sp = dp = row; i < row_width; i++)
            {
               png_byte save[2];
               save[0] = *(sp++);
               save[1] = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = save[0];
               *(dp++) = save[1];
            }
         }
      }
      else if (row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      {
         /* This converts from AG to GA */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp, dp;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            for (i = 0, sp = dp = row; i < row_width; i++)
            {
               png_byte save = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = save;
            }
         }
         /* This converts from AAGG to GGAA */
         else
         {
            png_bytep sp, dp;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            for (i = 0, sp = dp = row; i < row_width; i++)
            {
               png_byte save[2];
               save[0] = *(sp++);
               save[1] = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = *(sp++);
               *(dp++) = save[0];
               *(dp++) = save[1];
            }
         }
      }
   }
