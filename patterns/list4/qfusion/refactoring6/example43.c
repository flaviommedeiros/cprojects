if (png_ptr->chunkdata + slength < ep
#ifdef PNG_FLOATING_POINT_SUPPORTED
      || width <= 0. || height <= 0.
#endif
      )
   {
      png_warning(png_ptr, "Invalid sCAL data");
      png_free(png_ptr, png_ptr->chunkdata);
      png_ptr->chunkdata = NULL;
#if defined(PNG_FIXED_POINT_SUPPORTED) && !defined(PNG_FLOATING_POINT_SUPPORTED)
      png_free(png_ptr, swidth);
      png_free(png_ptr, sheight);
#endif
      return;
   }
