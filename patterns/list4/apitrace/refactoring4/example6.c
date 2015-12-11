#ifdef PNG_WRITE_16BIT_SUPPORTED
if (png_ptr->bit_depth == 8 && (buf[0] | buf[2] | buf[4]) != 0)
#else
      if ((buf[0] | buf[2] | buf[4]) != 0)
#endif
      {
         png_warning(png_ptr,
             "Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8");

         return;
      }
