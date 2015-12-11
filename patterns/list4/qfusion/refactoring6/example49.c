if (
#ifdef PNG_USELESS_TESTS_SUPPORTED
       row != NULL  && row_info != NULL &&
#endif
       row_info->color_type == PNG_COLOR_TYPE_GRAY)
   {
      if (row_info->bit_depth == 8)
      {
         /* This changes the data from G to GX */
         if (flags & PNG_FLAG_FILLER_AFTER)
         {
            png_bytep sp = row + (png_size_t)row_width;
            png_bytep dp =  sp + (png_size_t)row_width;
            for (i = 1; i < row_width; i++)
            {
               *(--dp) = lo_filler;
               *(--dp) = *(--sp);
            }
            *(--dp) = lo_filler;
            row_info->channels = 2;
            row_info->pixel_depth = 16;
            row_info->rowbytes = row_width * 2;
         }
      /* This changes the data from G to XG */
         else
         {
            png_bytep sp = row + (png_size_t)row_width;
            png_bytep dp = sp  + (png_size_t)row_width;
            for (i = 0; i < row_width; i++)
            {
               *(--dp) = *(--sp);
               *(--dp) = lo_filler;
            }
            row_info->channels = 2;
            row_info->pixel_depth = 16;
            row_info->rowbytes = row_width * 2;
         }
      }
      else if (row_info->bit_depth == 16)
      {
         /* This changes the data from GG to GGXX */
         if (flags & PNG_FLAG_FILLER_AFTER)
         {
            png_bytep sp = row + (png_size_t)row_width * 2;
            png_bytep dp = sp  + (png_size_t)row_width * 2;
            for (i = 1; i < row_width; i++)
            {
               *(--dp) = hi_filler;
               *(--dp) = lo_filler;
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
            }
            *(--dp) = hi_filler;
            *(--dp) = lo_filler;
            row_info->channels = 2;
            row_info->pixel_depth = 32;
            row_info->rowbytes = row_width * 4;
         }
         /* This changes the data from GG to XXGG */
         else
         {
            png_bytep sp = row + (png_size_t)row_width * 2;
            png_bytep dp = sp  + (png_size_t)row_width * 2;
            for (i = 0; i < row_width; i++)
            {
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = hi_filler;
               *(--dp) = lo_filler;
            }
            row_info->channels = 2;
            row_info->pixel_depth = 32;
            row_info->rowbytes = row_width * 4;
         }
      }
   } /* COLOR_TYPE == GRAY */
   else if (row_info->color_type == PNG_COLOR_TYPE_RGB)
   {
      if (row_info->bit_depth == 8)
      {
         /* This changes the data from RGB to RGBX */
         if (flags & PNG_FLAG_FILLER_AFTER)
         {
            png_bytep sp = row + (png_size_t)row_width * 3;
            png_bytep dp = sp  + (png_size_t)row_width;
            for (i = 1; i < row_width; i++)
            {
               *(--dp) = lo_filler;
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
            }
            *(--dp) = lo_filler;
            row_info->channels = 4;
            row_info->pixel_depth = 32;
            row_info->rowbytes = row_width * 4;
         }
      /* This changes the data from RGB to XRGB */
         else
         {
            png_bytep sp = row + (png_size_t)row_width * 3;
            png_bytep dp = sp + (png_size_t)row_width;
            for (i = 0; i < row_width; i++)
            {
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = lo_filler;
            }
            row_info->channels = 4;
            row_info->pixel_depth = 32;
            row_info->rowbytes = row_width * 4;
         }
      }
      else if (row_info->bit_depth == 16)
      {
         /* This changes the data from RRGGBB to RRGGBBXX */
         if (flags & PNG_FLAG_FILLER_AFTER)
         {
            png_bytep sp = row + (png_size_t)row_width * 6;
            png_bytep dp = sp  + (png_size_t)row_width * 2;
            for (i = 1; i < row_width; i++)
            {
               *(--dp) = hi_filler;
               *(--dp) = lo_filler;
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
            }
            *(--dp) = hi_filler;
            *(--dp) = lo_filler;
            row_info->channels = 4;
            row_info->pixel_depth = 64;
            row_info->rowbytes = row_width * 8;
         }
         /* This changes the data from RRGGBB to XXRRGGBB */
         else
         {
            png_bytep sp = row + (png_size_t)row_width * 6;
            png_bytep dp = sp  + (png_size_t)row_width * 2;
            for (i = 0; i < row_width; i++)
            {
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = *(--sp);
               *(--dp) = hi_filler;
               *(--dp) = lo_filler;
            }
            row_info->channels = 4;
            row_info->pixel_depth = 64;
            row_info->rowbytes = row_width * 8;
         }
      }
   }
