#ifdef PNG_READ_EXPAND_16_SUPPORTED
if ((png_ptr->transformations & PNG_EXPAND_16) != 0)
   {
#  ifdef PNG_READ_EXPAND_SUPPORTED
      /* In fact it is an error if it isn't supported, but checking is
       * the safe way.
       */
      if ((png_ptr->transformations & PNG_EXPAND) != 0)
      {
         if (png_ptr->bit_depth < 16)
            max_pixel_depth *= 2;
      }
      else
#  endif
      png_ptr->transformations &= ~PNG_EXPAND_16;
   }
