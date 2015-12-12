#ifdef PNG_SET_USER_LIMITS_SUPPORTED
if (width > png_ptr->user_width_max)
#else
   if (width > PNG_USER_WIDTH_MAX)
#endif
   {
      png_warning(png_ptr, "Image width exceeds user limit in IHDR");
      error = 1;
   }
