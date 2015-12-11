#ifdef PNG_USELESS_TESTS_SUPPORTED
if (row != NULL && row_info != NULL)
#endif
   {
      png_bytep sp=row;
      png_bytep dp=row;
      png_uint_32 row_width=row_info->width;
      png_uint_32 i;

      if ((row_info->color_type == PNG_COLOR_TYPE_RGB ||
          (row_info->color_type == PNG_COLOR_TYPE_RGB_ALPHA &&
          (flags & PNG_FLAG_STRIP_ALPHA))) &&
          row_info->channels == 4)
      {
         if (row_info->bit_depth == 8)
         {
            /* This converts from RGBX or RGBA to RGB */
            if (flags & PNG_FLAG_FILLER_AFTER)
            {
               dp+=3; sp+=4;
               for (i = 1; i < row_width; i++)
               {
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  sp++;
               }
            }
            /* This converts from XRGB or ARGB to RGB */
            else
            {
               for (i = 0; i < row_width; i++)
               {
                  sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
               }
            }
            row_info->pixel_depth = 24;
            row_info->rowbytes = row_width * 3;
         }
         else /* if (row_info->bit_depth == 16) */
         {
            if (flags & PNG_FLAG_FILLER_AFTER)
            {
               /* This converts from RRGGBBXX or RRGGBBAA to RRGGBB */
               sp += 8; dp += 6;
               for (i = 1; i < row_width; i++)
               {
                  /* This could be (although png_memcpy is probably slower):
                  png_memcpy(dp, sp, 6);
                  sp += 8;
                  dp += 6;
                  */

                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  sp += 2;
               }
            }
            else
            {
               /* This converts from XXRRGGBB or AARRGGBB to RRGGBB */
               for (i = 0; i < row_width; i++)
               {
                  /* This could be (although png_memcpy is probably slower):
                  png_memcpy(dp, sp, 6);
                  sp += 8;
                  dp += 6;
                  */

                  sp+=2;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
               }
            }
            row_info->pixel_depth = 48;
            row_info->rowbytes = row_width * 6;
         }
         row_info->channels = 3;
      }
      else if ((row_info->color_type == PNG_COLOR_TYPE_GRAY ||
         (row_info->color_type == PNG_COLOR_TYPE_GRAY_ALPHA &&
         (flags & PNG_FLAG_STRIP_ALPHA))) &&
          row_info->channels == 2)
      {
         if (row_info->bit_depth == 8)
         {
            /* This converts from GX or GA to G */
            if (flags & PNG_FLAG_FILLER_AFTER)
            {
               for (i = 0; i < row_width; i++)
               {
                  *dp++ = *sp++;
                  sp++;
               }
            }
            /* This converts from XG or AG to G */
            else
            {
               for (i = 0; i < row_width; i++)
               {
                  sp++;
                  *dp++ = *sp++;
               }
            }
            row_info->pixel_depth = 8;
            row_info->rowbytes = row_width;
         }
         else /* if (row_info->bit_depth == 16) */
         {
            if (flags & PNG_FLAG_FILLER_AFTER)
            {
               /* This converts from GGXX or GGAA to GG */
               sp += 4; dp += 2;
               for (i = 1; i < row_width; i++)
               {
                  *dp++ = *sp++;
                  *dp++ = *sp++;
                  sp += 2;
               }
            }
            else
            {
               /* This converts from XXGG or AAGG to GG */
               for (i = 0; i < row_width; i++)
               {
                  sp += 2;
                  *dp++ = *sp++;
                  *dp++ = *sp++;
               }
            }
            row_info->pixel_depth = 16;
            row_info->rowbytes = row_width * 2;
         }
         row_info->channels = 1;
      }
      if (flags & PNG_FLAG_STRIP_ALPHA)
        row_info->color_type &= ~PNG_COLOR_MASK_ALPHA;
   }
