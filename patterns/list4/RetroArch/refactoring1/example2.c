if (strstr(path, ".tga"))
      return texture_image_load_tga_shift(path, out_img, a_shift, r_shift, g_shift, b_shift);
#ifdef HAVE_ZLIB
   else if (strstr(path, ".png"))
   {
      RARCH_LOG("[RPNG]: Using RPNG loader.\n");
      bool ret = rpng_load_image_argb(path, &out_img->pixels, &out_img->width, &out_img->height);
      if (!ret)
         return false;

      // This is quite uncommon ...
      if (a_shift != 24 || r_shift != 16 || g_shift != 8 || b_shift != 0)
      {
         unsigned num_pixels = out_img->width * out_img->height;
         uint32_t *pixels = out_img->pixels;
         for (unsigned i = 0; i < num_pixels; i++)
         {
            uint32_t col = pixels[i];
            uint8_t a = (uint8_t)(col >> 24);
            uint8_t r = (uint8_t)(col >> 16);
            uint8_t g = (uint8_t)(col >>  8);
            uint8_t b = (uint8_t)(col >>  0);
            pixels[i] = (a << a_shift) | (r << r_shift) | (g << g_shift) | (b << b_shift);
         }
      }

      return true;
   }
#endif
