if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_cHRM)
#ifdef PNG_READ_sRGB_SUPPORTED
      && !(info_ptr->valid & PNG_INFO_sRGB)
#endif
      )
   {
      png_warning(png_ptr, "Duplicate cHRM chunk");
      png_crc_finish(png_ptr, length);
      return;
   }
