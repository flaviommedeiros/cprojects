if (row_info->bit_depth == 8 &&
#ifdef PNG_USELESS_TESTS_SUPPORTED
       row != NULL && row_info != NULL &&
#endif
      row_info->channels == 1)
   {
      switch ((int)bit_depth)
      {
         case 1:
         {
            png_bytep sp, dp;
            int mask, v;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            sp = row;
            dp = row;
            mask = 0x80;
            v = 0;

            for (i = 0; i < row_width; i++)
            {
               if (*sp != 0)
                  v |= mask;
               sp++;
               if (mask > 1)
                  mask >>= 1;
               else
               {
                  mask = 0x80;
                  *dp = (png_byte)v;
                  dp++;
                  v = 0;
               }
            }
            if (mask != 0x80)
               *dp = (png_byte)v;
            break;
         }
         case 2:
         {
            png_bytep sp, dp;
            int shift, v;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            sp = row;
            dp = row;
            shift = 6;
            v = 0;
            for (i = 0; i < row_width; i++)
            {
               png_byte value;

               value = (png_byte)(*sp & 0x03);
               v |= (value << shift);
               if (shift == 0)
               {
                  shift = 6;
                  *dp = (png_byte)v;
                  dp++;
                  v = 0;
               }
               else
                  shift -= 2;
               sp++;
            }
            if (shift != 6)
               *dp = (png_byte)v;
            break;
         }
         case 4:
         {
            png_bytep sp, dp;
            int shift, v;
            png_uint_32 i;
            png_uint_32 row_width = row_info->width;

            sp = row;
            dp = row;
            shift = 4;
            v = 0;
            for (i = 0; i < row_width; i++)
            {
               png_byte value;

               value = (png_byte)(*sp & 0x0f);
               v |= (value << shift);

               if (shift == 0)
               {
                  shift = 4;
                  *dp = (png_byte)v;
                  dp++;
                  v = 0;
               }
               else
                  shift -= 4;

               sp++;
            }
            if (shift != 4)
               *dp = (png_byte)v;
            break;
         }
      }
      row_info->bit_depth = (png_byte)bit_depth;
      row_info->pixel_depth = (png_byte)(bit_depth * row_info->channels);
      row_info->rowbytes = PNG_ROWBYTES(row_info->pixel_depth,
         row_info->width);
   }
