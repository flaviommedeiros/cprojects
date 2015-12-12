#if defined(PNG_USELESS_TESTS_SUPPORTED)
if(png_ptr != NULL)
#endif
  {
#if defined(PNG_READ_BACKGROUND_SUPPORTED) || defined(PNG_READ_SHIFT_SUPPORTED) \
 || defined(PNG_READ_GAMMA_SUPPORTED)
   int color_type = png_ptr->color_type;
#endif

#if defined(PNG_READ_EXPAND_SUPPORTED) && defined(PNG_READ_BACKGROUND_SUPPORTED)
   if ((png_ptr->transformations & PNG_BACKGROUND_EXPAND) &&
       (png_ptr->transformations & PNG_EXPAND))
   {
      if (!(color_type & PNG_COLOR_MASK_COLOR))  /* i.e., GRAY or GRAY_ALPHA */
      {
         /* expand background and tRNS chunks */
         switch (png_ptr->bit_depth)
         {
            case 1:
               png_ptr->background.gray *= (png_uint_16)0xff;
               png_ptr->background.red = png_ptr->background.green
                 =  png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0xff;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 2:
               png_ptr->background.gray *= (png_uint_16)0x55;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0x55;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 4:
               png_ptr->background.gray *= (png_uint_16)0x11;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0x11;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 8:
            case 16:
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               break;
         }
      }
      else if (color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_ptr->background.red   =
            png_ptr->palette[png_ptr->background.index].red;
         png_ptr->background.green =
            png_ptr->palette[png_ptr->background.index].green;
         png_ptr->background.blue  =
            png_ptr->palette[png_ptr->background.index].blue;

#if defined(PNG_READ_INVERT_ALPHA_SUPPORTED)
        if (png_ptr->transformations & PNG_INVERT_ALPHA)
        {
#if defined(PNG_READ_EXPAND_SUPPORTED)
           if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
#endif
           {
           /* invert the alpha channel (in tRNS) unless the pixels are
              going to be expanded, in which case leave it for later */
              int i,istop;
              istop=(int)png_ptr->num_trans;
              for (i=0; i<istop; i++)
                 png_ptr->trans[i] = (png_byte)(255 - png_ptr->trans[i]);
           }
        }
#endif

      }
   }
#endif

#if defined(PNG_READ_BACKGROUND_SUPPORTED) && defined(PNG_READ_GAMMA_SUPPORTED)
   png_ptr->background_1 = png_ptr->background;
#endif
#if defined(PNG_READ_GAMMA_SUPPORTED) && defined(PNG_FLOATING_POINT_SUPPORTED)

   if ((color_type == PNG_COLOR_TYPE_PALETTE && png_ptr->num_trans != 0)
       && (fabs(png_ptr->screen_gamma * png_ptr->gamma - 1.0)
         < PNG_GAMMA_THRESHOLD))
   {
    int i,k;
    k=0;
    for (i=0; i<png_ptr->num_trans; i++)
    {
      if (png_ptr->trans[i] != 0 && png_ptr->trans[i] != 0xff)
        k=1; /* partial transparency is present */
    }
    if (k == 0)
      png_ptr->transformations &= (~PNG_GAMMA);
   }

   if ((png_ptr->transformations & (PNG_GAMMA | PNG_RGB_TO_GRAY)) &&
        png_ptr->gamma != 0.0)
   {
      png_build_gamma_table(png_ptr);
#if defined(PNG_READ_BACKGROUND_SUPPORTED)
      if (png_ptr->transformations & PNG_BACKGROUND)
      {
         if (color_type == PNG_COLOR_TYPE_PALETTE)
         {
           /* could skip if no transparency and
           */
            png_color back, back_1;
            png_colorp palette = png_ptr->palette;
            int num_palette = png_ptr->num_palette;
            int i;
            if (png_ptr->background_gamma_type == PNG_BACKGROUND_GAMMA_FILE)
            {
               back.red = png_ptr->gamma_table[png_ptr->background.red];
               back.green = png_ptr->gamma_table[png_ptr->background.green];
               back.blue = png_ptr->gamma_table[png_ptr->background.blue];

               back_1.red = png_ptr->gamma_to_1[png_ptr->background.red];
               back_1.green = png_ptr->gamma_to_1[png_ptr->background.green];
               back_1.blue = png_ptr->gamma_to_1[png_ptr->background.blue];
            }
            else
            {
               double g, gs;

               switch (png_ptr->background_gamma_type)
               {
                  case PNG_BACKGROUND_GAMMA_SCREEN:
                     g = (png_ptr->screen_gamma);
                     gs = 1.0;
                     break;
                  case PNG_BACKGROUND_GAMMA_FILE:
                     g = 1.0 / (png_ptr->gamma);
                     gs = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
                     break;
                  case PNG_BACKGROUND_GAMMA_UNIQUE:
                     g = 1.0 / (png_ptr->background_gamma);
                     gs = 1.0 / (png_ptr->background_gamma *
                                 png_ptr->screen_gamma);
                     break;
                  default:
                     g = 1.0;    /* back_1 */
                     gs = 1.0;   /* back */
               }

               if ( fabs(gs - 1.0) < PNG_GAMMA_THRESHOLD)
               {
                  back.red   = (png_byte)png_ptr->background.red;
                  back.green = (png_byte)png_ptr->background.green;
                  back.blue  = (png_byte)png_ptr->background.blue;
               }
               else
               {
                  back.red = (png_byte)(pow(
                     (double)png_ptr->background.red/255, gs) * 255.0 + .5);
                  back.green = (png_byte)(pow(
                     (double)png_ptr->background.green/255, gs) * 255.0 + .5);
                  back.blue = (png_byte)(pow(
                     (double)png_ptr->background.blue/255, gs) * 255.0 + .5);
               }

               back_1.red = (png_byte)(pow(
                  (double)png_ptr->background.red/255, g) * 255.0 + .5);
               back_1.green = (png_byte)(pow(
                  (double)png_ptr->background.green/255, g) * 255.0 + .5);
               back_1.blue = (png_byte)(pow(
                  (double)png_ptr->background.blue/255, g) * 255.0 + .5);
            }
            for (i = 0; i < num_palette; i++)
            {
               if (i < (int)png_ptr->num_trans && png_ptr->trans[i] != 0xff)
               {
                  if (png_ptr->trans[i] == 0)
                  {
                     palette[i] = back;
                  }
                  else /* if (png_ptr->trans[i] != 0xff) */
                  {
                     png_byte v, w;

                     v = png_ptr->gamma_to_1[palette[i].red];
                     png_composite(w, v, png_ptr->trans[i], back_1.red);
                     palette[i].red = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].green];
                     png_composite(w, v, png_ptr->trans[i], back_1.green);
                     palette[i].green = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].blue];
                     png_composite(w, v, png_ptr->trans[i], back_1.blue);
                     palette[i].blue = png_ptr->gamma_from_1[w];
                  }
               }
               else
               {
                  palette[i].red = png_ptr->gamma_table[palette[i].red];
                  palette[i].green = png_ptr->gamma_table[palette[i].green];
                  palette[i].blue = png_ptr->gamma_table[palette[i].blue];
               }
            }
         }
         /* if (png_ptr->background_gamma_type!=PNG_BACKGROUND_GAMMA_UNKNOWN) */
         else
         /* color_type != PNG_COLOR_TYPE_PALETTE */
         {
            double m = (double)(((png_uint_32)1 << png_ptr->bit_depth) - 1);
            double g = 1.0;
            double gs = 1.0;

            switch (png_ptr->background_gamma_type)
            {
               case PNG_BACKGROUND_GAMMA_SCREEN:
                  g = (png_ptr->screen_gamma);
                  gs = 1.0;
                  break;
               case PNG_BACKGROUND_GAMMA_FILE:
                  g = 1.0 / (png_ptr->gamma);
                  gs = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
                  break;
               case PNG_BACKGROUND_GAMMA_UNIQUE:
                  g = 1.0 / (png_ptr->background_gamma);
                  gs = 1.0 / (png_ptr->background_gamma *
                     png_ptr->screen_gamma);
                  break;
            }

            png_ptr->background_1.gray = (png_uint_16)(pow(
               (double)png_ptr->background.gray / m, g) * m + .5);
            png_ptr->background.gray = (png_uint_16)(pow(
               (double)png_ptr->background.gray / m, gs) * m + .5);

            if ((png_ptr->background.red != png_ptr->background.green) ||
                (png_ptr->background.red != png_ptr->background.blue) ||
                (png_ptr->background.red != png_ptr->background.gray))
            {
               /* RGB or RGBA with color background */
               png_ptr->background_1.red = (png_uint_16)(pow(
                  (double)png_ptr->background.red / m, g) * m + .5);
               png_ptr->background_1.green = (png_uint_16)(pow(
                  (double)png_ptr->background.green / m, g) * m + .5);
               png_ptr->background_1.blue = (png_uint_16)(pow(
                  (double)png_ptr->background.blue / m, g) * m + .5);
               png_ptr->background.red = (png_uint_16)(pow(
                  (double)png_ptr->background.red / m, gs) * m + .5);
               png_ptr->background.green = (png_uint_16)(pow(
                  (double)png_ptr->background.green / m, gs) * m + .5);
               png_ptr->background.blue = (png_uint_16)(pow(
                  (double)png_ptr->background.blue / m, gs) * m + .5);
            }
            else
            {
               /* GRAY, GRAY ALPHA, RGB, or RGBA with gray background */
               png_ptr->background_1.red = png_ptr->background_1.green
                 = png_ptr->background_1.blue = png_ptr->background_1.gray;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
            }
         }
      }
      else
      /* transformation does not include PNG_BACKGROUND */
#endif /* PNG_READ_BACKGROUND_SUPPORTED */
      if (color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_colorp palette = png_ptr->palette;
         int num_palette = png_ptr->num_palette;
         int i;

         for (i = 0; i < num_palette; i++)
         {
            palette[i].red = png_ptr->gamma_table[palette[i].red];
            palette[i].green = png_ptr->gamma_table[palette[i].green];
            palette[i].blue = png_ptr->gamma_table[palette[i].blue];
         }
      }
   }
#if defined(PNG_READ_BACKGROUND_SUPPORTED)
   else
#endif
#endif /* PNG_READ_GAMMA_SUPPORTED && PNG_FLOATING_POINT_SUPPORTED */
#if defined(PNG_READ_BACKGROUND_SUPPORTED)
   /* No GAMMA transformation */
   if ((png_ptr->transformations & PNG_BACKGROUND) &&
       (color_type == PNG_COLOR_TYPE_PALETTE))
   {
      int i;
      int istop = (int)png_ptr->num_trans;
      png_color back;
      png_colorp palette = png_ptr->palette;

      back.red   = (png_byte)png_ptr->background.red;
      back.green = (png_byte)png_ptr->background.green;
      back.blue  = (png_byte)png_ptr->background.blue;

      for (i = 0; i < istop; i++)
      {
         if (png_ptr->trans[i] == 0)
         {
            palette[i] = back;
         }
         else if (png_ptr->trans[i] != 0xff)
         {
            /* The png_composite() macro is defined in png.h */
            png_composite(palette[i].red, palette[i].red,
               png_ptr->trans[i], back.red);
            png_composite(palette[i].green, palette[i].green,
               png_ptr->trans[i], back.green);
            png_composite(palette[i].blue, palette[i].blue,
               png_ptr->trans[i], back.blue);
         }
      }
   }
#endif /* PNG_READ_BACKGROUND_SUPPORTED */

#if defined(PNG_READ_SHIFT_SUPPORTED)
   if ((png_ptr->transformations & PNG_SHIFT) &&
      (color_type == PNG_COLOR_TYPE_PALETTE))
   {
      png_uint_16 i;
      png_uint_16 istop = png_ptr->num_palette;
      int sr = 8 - png_ptr->sig_bit.red;
      int sg = 8 - png_ptr->sig_bit.green;
      int sb = 8 - png_ptr->sig_bit.blue;

      if (sr < 0 || sr > 8)
         sr = 0;
      if (sg < 0 || sg > 8)
         sg = 0;
      if (sb < 0 || sb > 8)
         sb = 0;
      for (i = 0; i < istop; i++)
      {
         png_ptr->palette[i].red >>= sr;
         png_ptr->palette[i].green >>= sg;
         png_ptr->palette[i].blue >>= sb;
      }
   }
#endif  /* PNG_READ_SHIFT_SUPPORTED */
 }
