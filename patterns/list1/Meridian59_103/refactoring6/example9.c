if ((
#ifdef PNG_MNG_FEATURES_SUPPORTED
       !(png_ptr->mng_features_permitted & PNG_FLAG_MNG_EMPTY_PLTE) &&
#endif
       num_pal == 0) || num_pal > 256)
   {
      if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_error(png_ptr, "Invalid number of colors in palette");
      }

      else
      {
         png_warning(png_ptr, "Invalid number of colors in palette");
         return;
      }
   }
