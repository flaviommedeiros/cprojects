if (
#if defined(PNG_USELESS_TESTS_SUPPORTED)
       row != NULL && row_info != NULL &&
#endif
       row_info->bit_depth < 8)
   {
      png_bytep rp, end, table;

      end = row + row_info->rowbytes;

      if (row_info->bit_depth == 1)
         table = (png_bytep)onebppswaptable;
      else if (row_info->bit_depth == 2)
         table = (png_bytep)twobppswaptable;
      else if (row_info->bit_depth == 4)
         table = (png_bytep)fourbppswaptable;
      else
         return;

      for (rp = row; rp < end; rp++)
         *rp = table[*rp];
   }
