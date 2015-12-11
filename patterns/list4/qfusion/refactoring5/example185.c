#ifdef PNG_READ_GAMMA_SUPPORTED
if (png_ptr->transformations & PNG_GAMMA)
   {
      int i;

      for (i = 0; i < num_palette; i++)
      {
         palette[i].red = png_ptr->gamma_table[palette[i].red];
         palette[i].green = png_ptr->gamma_table[palette[i].green];
         palette[i].blue = png_ptr->gamma_table[palette[i].blue];
      }
   }
#ifdef PNG_READ_BACKGROUND_SUPPORTED
   else
#endif
#endif
#ifdef PNG_READ_BACKGROUND_SUPPORTED
   if (png_ptr->transformations & PNG_BACKGROUND)
   {
      if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_color back;

         back.red   = (png_byte)png_ptr->background.red;
         back.green = (png_byte)png_ptr->background.green;
         back.blue  = (png_byte)png_ptr->background.blue;

         for (i = 0; i < (int)png_ptr->num_trans; i++)
         {
            if (png_ptr->trans[i] == 0)
            {
               palette[i].red = back.red;
               palette[i].green = back.green;
               palette[i].blue = back.blue;
            }
            else if (png_ptr->trans[i] != 0xff)
            {
               png_composite(palette[i].red, png_ptr->palette[i].red,
                  png_ptr->trans[i], back.red);
               png_composite(palette[i].green, png_ptr->palette[i].green,
                  png_ptr->trans[i], back.green);
               png_composite(palette[i].blue, png_ptr->palette[i].blue,
                  png_ptr->trans[i], back.blue);
            }
         }
      }
      else /* Assume grayscale palette (what else could it be?) */
      {
         int i;

         for (i = 0; i < num_palette; i++)
         {
            if (i == (png_byte)png_ptr->trans_values.gray)
            {
               palette[i].red = (png_byte)png_ptr->background.red;
               palette[i].green = (png_byte)png_ptr->background.green;
               palette[i].blue = (png_byte)png_ptr->background.blue;
            }
         }
      }
   }
