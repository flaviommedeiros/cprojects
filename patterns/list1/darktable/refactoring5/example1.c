#ifdef PNG_iCCP_SUPPORTED
if(png_get_valid(image.png_ptr, image.info_ptr, PNG_INFO_iCCP) != 0
     && png_get_iCCP(image.png_ptr, image.info_ptr, &name, &compression_type, &profile, &proflen) != 0)
  {
    *out = (uint8_t *)malloc(proflen);
    memcpy(*out, profile, proflen);
  }
  else
#endif
    proflen = 0;
