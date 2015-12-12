#if defined(PNG_USELESS_TESTS_SUPPORTED)
if (row != NULL && row_info != NULL)
#endif
   {
      if (row_info->color_type == PNG_COLOR_TYPE_GRAY)
      {
         png_uint_16 gray = (png_uint_16)(trans_value ? trans_value->gray : 0);

         if (row_info->bit_depth < 8)
         {
            switch (row_info->bit_depth)
            {
               case 1:
               {
                  gray = (png_uint_16)(gray*0xff);
                  sp = row + (png_size_t)((row_width - 1) >> 3);
                  dp = row + (png_size_t)row_width - 1;
                  shift = 7 - (int)((row_width + 7) & 0x07);
                  for (i = 0; i < row_width; i++)
                  {
                     if ((*sp >> shift) & 0x01)
                        *dp = 0xff;
                     else
                        *dp = 0;
                     if (shift == 7)
                     {
                        shift = 0;
                        sp--;
                     }
                     else
                        shift++;

                     dp--;
                  }
                  break;
               }
               case 2:
               {
                  gray = (png_uint_16)(gray*0x55);
                  sp = row + (png_size_t)((row_width - 1) >> 2);
                  dp = row + (png_size_t)row_width - 1;
                  shift = (int)((3 - ((row_width + 3) & 0x03)) << 1);
                  for (i = 0; i < row_width; i++)
                  {
                     value = (*sp >> shift) & 0x03;
                     *dp = (png_byte)(value | (value << 2) | (value << 4) |
                        (value << 6));
                     if (shift == 6)
                     {
                        shift = 0;
                        sp--;
                     }
                     else
                        shift += 2;

                     dp--;
                  }
                  break;
               }
               case 4:
               {
                  gray = (png_uint_16)(gray*0x11);
                  sp = row + (png_size_t)((row_width - 1) >> 1);
                  dp = row + (png_size_t)row_width - 1;
                  shift = (int)((1 - ((row_width + 1) & 0x01)) << 2);
                  for (i = 0; i < row_width; i++)
                  {
                     value = (*sp >> shift) & 0x0f;
                     *dp = (png_byte)(value | (value << 4));
                     if (shift == 4)
                     {
                        shift = 0;
                        sp--;
                     }
                     else
                        shift = 4;

                     dp--;
                  }
                  break;
               }
            }
            row_info->bit_depth = 8;
            row_info->pixel_depth = 8;
            row_info->rowbytes = row_width;
         }

         if (trans_value != NULL)
         {
            if (row_info->bit_depth == 8)
            {
               sp = row + (png_size_t)row_width - 1;
               dp = row + (png_size_t)(row_width << 1) - 1;
               for (i = 0; i < row_width; i++)
               {
                  if (*sp == gray)
                     *dp-- = 0;
                  else
                     *dp-- = 0xff;
                  *dp-- = *sp--;
               }
            }
            else if (row_info->bit_depth == 16)
            {
               sp = row + row_info->rowbytes - 1;
               dp = row + (row_info->rowbytes << 1) - 1;
               for (i = 0; i < row_width; i++)
               {
                  if (((png_uint_16)*(sp) |
                     ((png_uint_16)*(sp - 1) << 8)) == gray)
                  {
                     *dp-- = 0;
                     *dp-- = 0;
                  }
                  else
                  {
                     *dp-- = 0xff;
                     *dp-- = 0xff;
                  }
                  *dp-- = *sp--;
                  *dp-- = *sp--;
               }
            }
            row_info->color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
            row_info->channels = 2;
            row_info->pixel_depth = (png_byte)(row_info->bit_depth << 1);
            row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth,
               row_width);
         }
      }
      else if (row_info->color_type == PNG_COLOR_TYPE_RGB && trans_value)
      {
         if (row_info->bit_depth == 8)
         {
            sp = row + (png_size_t)row_info->rowbytes - 1;
            dp = row + (png_size_t)(row_width << 2) - 1;
            for (i = 0; i < row_width; i++)
            {
               if (*(sp - 2) == trans_value->red &&
                  *(sp - 1) == trans_value->green &&
                  *(sp - 0) == trans_value->blue)
                  *dp-- = 0;
               else
                  *dp-- = 0xff;
               *dp-- = *sp--;
               *dp-- = *sp--;
               *dp-- = *sp--;
            }
         }
         else if (row_info->bit_depth == 16)
         {
            sp = row + row_info->rowbytes - 1;
            dp = row + (png_size_t)(row_width << 3) - 1;
            for (i = 0; i < row_width; i++)
            {
               if ((((png_uint_16)*(sp - 4) |
                  ((png_uint_16)*(sp - 5) << 8)) == trans_value->red) &&
                  (((png_uint_16)*(sp - 2) |
                  ((png_uint_16)*(sp - 3) << 8)) == trans_value->green) &&
                  (((png_uint_16)*(sp - 0) |
                  ((png_uint_16)*(sp - 1) << 8)) == trans_value->blue))
               {
                  *dp-- = 0;
                  *dp-- = 0;
               }
               else
               {
                  *dp-- = 0xff;
                  *dp-- = 0xff;
               }
               *dp-- = *sp--;
               *dp-- = *sp--;
               *dp-- = *sp--;
               *dp-- = *sp--;
               *dp-- = *sp--;
               *dp-- = *sp--;
            }
         }
         row_info->color_type = PNG_COLOR_TYPE_RGB_ALPHA;
         row_info->channels = 4;
         row_info->pixel_depth = (png_byte)(row_info->bit_depth << 2);
         row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth,row_width);
      }
   }
