#ifdef PNG_FLOATING_POINT_SUPPORTED
if (white_x > (double) PNG_UINT_31_MAX ||
       white_y > (double) PNG_UINT_31_MAX ||
         red_x > (double) PNG_UINT_31_MAX ||
         red_y > (double) PNG_UINT_31_MAX ||
       green_x > (double) PNG_UINT_31_MAX ||
       green_y > (double) PNG_UINT_31_MAX ||
        blue_x > (double) PNG_UINT_31_MAX ||
        blue_y > (double) PNG_UINT_31_MAX)
#else
   if (white_x > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
       white_y > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
         red_x > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
         red_y > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
       green_x > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
       green_y > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
        blue_x > (png_fixed_point) PNG_UINT_31_MAX/100000L ||
        blue_y > (png_fixed_point) PNG_UINT_31_MAX/100000L)
#endif
   {
      png_warning(png_ptr,
        "Ignoring attempt to set chromaticity value exceeding 21474.83");
      return;
   }
