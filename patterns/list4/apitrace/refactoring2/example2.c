#if PNG_sRGB_PROFILE_CHECKS >= 0
if (png_compare_ICC_profile_with_sRGB(png_ptr, profile, adler) != 0)
#endif
      (void)png_colorspace_set_sRGB(png_ptr, colorspace,
         (int)/*already checked*/png_get_uint_32(profile+64));
