if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL &&
#endif
       row_info->bit_depth == 16)
   {
      png_bytep rp = row;
      png_uint_32 i;
      png_uint_32 istop= row_info->width * row_info->channels;

      for (i = 0; i < istop; i++, rp += 2)
      {
         png_byte t = *rp;
         *rp = *(rp + 1);
         *(rp + 1) = t;
      }
   }
