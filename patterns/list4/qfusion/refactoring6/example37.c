if (
#ifdef PNG_USELESS_TESTS_SUPPORTED
       row != NULL && row_info != NULL &&
#endif
       (row_info->color_type & PNG_COLOR_MASK_COLOR))
   {
      int bytes_per_pixel;
      png_uint_32 row_width = row_info->width;
      if (row_info->bit_depth == 8)
      {
         png_bytep rp;
         png_uint_32 i;

         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
            bytes_per_pixel = 3;
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
            bytes_per_pixel = 4;
         else
            return;

         for (i = 0, rp = row; i < row_width; i++, rp += bytes_per_pixel)
         {
            *(rp)   = (png_byte)((*rp     - *(rp+1))&0xff);
            *(rp+2) = (png_byte)((*(rp+2) - *(rp+1))&0xff);
         }
      }
      else if (row_info->bit_depth == 16)
      {
         png_bytep rp;
         png_uint_32 i;

         if (row_info->color_type == PNG_COLOR_TYPE_RGB)
            bytes_per_pixel = 6;
         else if (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA)
            bytes_per_pixel = 8;
         else
            return;

         for (i = 0, rp = row; i < row_width; i++, rp += bytes_per_pixel)
         {
            png_uint_32 s0   = (*(rp  ) << 8) | *(rp+1);
            png_uint_32 s1   = (*(rp+2) << 8) | *(rp+3);
            png_uint_32 s2   = (*(rp+4) << 8) | *(rp+5);
            png_uint_32 red  = (png_uint_32)((s0 - s1) & 0xffffL);
            png_uint_32 blue = (png_uint_32)((s2 - s1) & 0xffffL);
            *(rp  ) = (png_byte)((red >> 8) & 0xff);
            *(rp+1) = (png_byte)(red & 0xff);
            *(rp+4) = (png_byte)((blue >> 8) & 0xff);
            *(rp+5) = (png_byte)(blue & 0xff);
         }
      }
   }
