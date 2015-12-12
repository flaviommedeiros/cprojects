#ifdef PNG_CHECK_cHRM_SUPPORTED
if (png_check_cHRM_fixed(png_ptr, int_white_x, int_white_y,
      int_red_x, int_red_y, int_green_x, int_green_y, int_blue_x, int_blue_y))
#endif
   {
      /* Each value is saved in 1/100,000ths */

      png_save_uint_32(buf, int_white_x);
      png_save_uint_32(buf + 4, int_white_y);

      png_save_uint_32(buf + 8, int_red_x);
      png_save_uint_32(buf + 12, int_red_y);

      png_save_uint_32(buf + 16, int_green_x);
      png_save_uint_32(buf + 20, int_green_y);

      png_save_uint_32(buf + 24, int_blue_x);
      png_save_uint_32(buf + 28, int_blue_y);

      png_write_chunk(png_ptr, (png_bytep)png_cHRM, buf, (png_size_t)32);
   }
