#ifdef PNG_SET_USER_LIMITS_SUPPORTED
if (height > png_ptr->user_height_max)
#else
   if (height > PNG_USER_HEIGHT_MAX)
#endif
   {
      png_warning(png_ptr, "Image height exceeds user limit in IHDR");
      error = 1;
   }
