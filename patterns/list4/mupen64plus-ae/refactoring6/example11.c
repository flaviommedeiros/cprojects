if (
#ifdef PNG_MNG_FEATURES_SUPPORTED
          (png_ptr->num_palette ||
          (!(png_ptr->mng_features_permitted & PNG_FLAG_MNG_EMPTY_PLTE))) &&
#endif
         back->index >= png_ptr->num_palette)
      {
         png_warning(png_ptr, "Invalid background palette index");
         return;
      }
