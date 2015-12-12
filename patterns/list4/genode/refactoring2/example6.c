#if defined(PNG_USELESS_TESTS_SUPPORTED)
if (row != NULL && row_info != NULL)
#endif
   {
      png_uint_32 row_width = row_info->width;
      if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
      {
         /* This converts from RGBA to ARGB */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_byte save;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               save = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = save;
            }
         }
         /* This converts from RRGGBBAA to AARRGGBB */
         else
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_byte save[2];
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               save[0] = *(--sp);
               save[1] = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = save[0];
               *(--dp) = save[1];
            }
         }
      }
      else if (row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
      {
         /* This converts from GA to AG */
         if (row_info->bit_depth == 8)
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_byte save;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               save = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = save;
            }
         }
         /* This converts from GGAA to AAGG */
         else
         {
            png_bytep sp = row + row_info->rowbytes;
            png_bytep dp = sp;
            png_byte save[2];
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               save[0] = *(--sp);
               save[1] = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = save[0];
               *(--dp) = save[1];
            }
         }
      }
   }
