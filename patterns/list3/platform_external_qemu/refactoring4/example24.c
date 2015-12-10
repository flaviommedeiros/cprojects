#if defined(PNG_USELESS_TESTS_SUPPORTED)
if (row != NULL && row_info != NULL && row_info->bit_depth == 16)
#else
   if (row_info->bit_depth == 16)
#endif
   {
      png_bytep sp = row;
      png_bytep dp = row;
      png_uint_32 i;
      png_uint_32 istop = row_info->width * row_info->channels;

      for (i = 0; i<istop; i++, sp += 2, dp++)
      {
#if defined(PNG_READ_16_TO_8_ACCURATE_SCALE_SUPPORTED)
      /* This does a more accurate scaling of the 16-bit color
       * value, rather than a simple low-byte truncation.
       *
       * What the ideal calculation should be:
       *   *dp = (((((png_uint_32)(*sp) << 8) |
       *          (png_uint_32)(*(sp + 1))) * 255 + 127) / (png_uint_32)65535L;
       *
       * GRR: no, I think this is what it really should be:
       *   *dp = (((((png_uint_32)(*sp) << 8) |
       *           (png_uint_32)(*(sp + 1))) + 128L) / (png_uint_32)257L;
       *
       * GRR: here's the exact calculation with shifts:
       *   temp = (((png_uint_32)(*sp) << 8) | (png_uint_32)(*(sp + 1))) + 128L;
       *   *dp = (temp - (temp >> 8)) >> 8;
       *
       * Approximate calculation with shift/add instead of multiply/divide:
       *   *dp = ((((png_uint_32)(*sp) << 8) |
       *          (png_uint_32)((int)(*(sp + 1)) - *sp)) + 128) >> 8;
       *
       * What we actually do to avoid extra shifting and conversion:
       */

         *dp = *sp + ((((int)(*(sp + 1)) - *sp) > 128) ? 1 : 0);
#else
       /* Simply discard the low order byte */
         *dp = *sp;
#endif
      }
      row_info->bit_depth = 8;
      row_info->pixel_depth = (png_byte)(8 * row_info->channels);
      row_info->rowbytes = row_info->width * row_info->channels;
   }
