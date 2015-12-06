#ifdef PNG_CHECK_cHRM_SUPPORTED
if (png_check_cHRM_fixed(png_ptr, white_x, white_y, red_x, red_y,
       green_x, green_y, blue_x, blue_y))
#endif
   {
      png_save_uint_32(buf, (png_uint_32)white_x);
      png_save_uint_32(buf + 4, (png_uint_32)white_y);

      png_save_uint_32(buf + 8, (png_uint_32)red_x);
      png_save_uint_32(buf + 12, (png_uint_32)red_y);

      png_save_uint_32(buf + 16, (png_uint_32)green_x);
      png_save_uint_32(buf + 20, (png_uint_32)green_y);

      png_save_uint_32(buf + 24, (png_uint_32)blue_x);
      png_save_uint_32(buf + 28, (png_uint_32)blue_y);

      png_write_complete_chunk(png_ptr, png_cHRM, buf, (png_size_t)32);
   }
