if (
#ifdef PNG_USELESS_TESTS_SUPPORTED
       row != NULL && row_info != NULL &&
#endif
       row_info->color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if (row_info->bit_depth < 8)
      {
         switch (row_info->bit_depth)
         {
            case 1:
            {
               sp = row + (png_size_t)((row_width - 1) >> 3);
               dp = row + (png_size_t)row_width - 1;
               shift = 7 - (int)((row_width + 7) & 0x07);
               for (i = 0; i < row_width; i++)
               {
                  if ((*sp >> shift) & 0x01)
                     *dp = 1;
                  else
                     *dp = 0;
                  if (shift == 7)
                  {
                     shift = 0;
                     sp--;
                  }
                  else
                     shift++;

                  dp--;
               }
               break;
            }

            case 2:
            {
               sp = row + (png_size_t)((row_width - 1) >> 2);
               dp = row + (png_size_t)row_width - 1;
               shift = (int)((3 - ((row_width + 3) & 0x03)) << 1);
               for (i = 0; i < row_width; i++)
               {
                  value = (*sp >> shift) & 0x03;
                  *dp = (png_byte)value;
                  if (shift == 6)
                  {
                     shift = 0;
                     sp--;
                  }
                  else
                     shift += 2;

                  dp--;
               }
               break;
            }

            case 4:
            {
               sp = row + (png_size_t)((row_width - 1) >> 1);
               dp = row + (png_size_t)row_width - 1;
               shift = (int)((row_width & 0x01) << 2);
               for (i = 0; i < row_width; i++)
               {
                  value = (*sp >> shift) & 0x0f;
                  *dp = (png_byte)value;
                  if (shift == 4)
                  {
                     shift = 0;
                     sp--;
                  }
                  else
                     shift += 4;

                  dp--;
               }
               break;
            }
         }
         row_info->bit_depth = 8;
         row_info->pixel_depth = 8;
         row_info->rowbytes = row_width;
      }
      switch (row_info->bit_depth)
      {
         case 8:
         {
            if (trans != NULL)
            {
               sp = row + (png_size_t)row_width - 1;
               dp = row + (png_size_t)(row_width << 2) - 1;

               for (i = 0; i < row_width; i++)
               {
                  if ((int)(*sp) >= num_trans)
                     *dp-- = 0xff;
                  else
                     *dp-- = trans[*sp];
                  *dp-- = palette[*sp].blue;
                  *dp-- = palette[*sp].green;
                  *dp-- = palette[*sp].red;
                  sp--;
               }
               row_info->bit_depth = 8;
               row_info->pixel_depth = 32;
               row_info->rowbytes = row_width * 4;
               row_info->color_type = 6;
               row_info->channels = 4;
            }
            else
            {
               sp = row + (png_size_t)row_width - 1;
               dp = row + (png_size_t)(row_width * 3) - 1;

               for (i = 0; i < row_width; i++)
               {
                  *dp-- = palette[*sp].blue;
                  *dp-- = palette[*sp].green;
                  *dp-- = palette[*sp].red;
                  sp--;
               }

               row_info->bit_depth = 8;
               row_info->pixel_depth = 24;
               row_info->rowbytes = row_width * 3;
               row_info->color_type = 2;
               row_info->channels = 3;
            }
            break;
         }
      }
   }
