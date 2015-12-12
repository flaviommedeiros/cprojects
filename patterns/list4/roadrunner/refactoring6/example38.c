if (
#if defined(PNG_MNG_FEATURES_SUPPORTED)
      !((png_ptr->mng_features_permitted & PNG_FLAG_MNG_FILTER_64) &&
      ((png_ptr->mode&PNG_HAVE_PNG_SIGNATURE) == 0) &&
      (color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_RGB_ALPHA) &&
      (filter_type == PNG_INTRAPIXEL_DIFFERENCING)) &&
#endif
      filter_type != PNG_FILTER_TYPE_BASE)
   {
      png_warning(png_ptr, "Invalid filter type specified");
      filter_type = PNG_FILTER_TYPE_BASE;
   }
