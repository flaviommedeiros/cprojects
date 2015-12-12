#ifdef PNG_READ_GAMMA_SUPPORTED
if (png_ptr->gamma_16_to_1 != NULL && png_ptr->gamma_16_from_1 != NULL)
         {
            png_bytep sp = row;
            png_bytep dp = row;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               png_uint_16 red, green, blue, w;
               png_byte hi,lo;

               hi=*(sp)++; lo=*(sp)++; red   = (png_uint_16)((hi << 8) | (lo));
               hi=*(sp)++; lo=*(sp)++; green = (png_uint_16)((hi << 8) | (lo));
               hi=*(sp)++; lo=*(sp)++; blue  = (png_uint_16)((hi << 8) | (lo));

               if (red == green && red == blue)
               {
                  if (png_ptr->gamma_16_table != NULL)
                     w = png_ptr->gamma_16_table[(red & 0xff)
                         >> png_ptr->gamma_shift][red >> 8];

                  else
                     w = red;
               }

               else
               {
                  png_uint_16 red_1   = png_ptr->gamma_16_to_1[(red & 0xff)
                      >> png_ptr->gamma_shift][red>>8];
                  png_uint_16 green_1 =
                      png_ptr->gamma_16_to_1[(green & 0xff) >>
                      png_ptr->gamma_shift][green>>8];
                  png_uint_16 blue_1  = png_ptr->gamma_16_to_1[(blue & 0xff)
                      >> png_ptr->gamma_shift][blue>>8];
                  png_uint_16 gray16  = (png_uint_16)((rc*red_1 + gc*green_1
                      + bc*blue_1 + 16384)>>15);
                  w = png_ptr->gamma_16_from_1[(gray16 & 0xff) >>
                      png_ptr->gamma_shift][gray16 >> 8];
                  rgb_error |= 1;
               }

               *(dp++) = (png_byte)((w>>8) & 0xff);
               *(dp++) = (png_byte)(w & 0xff);

               if (have_alpha != 0)
               {
                  *(dp++) = *(sp++);
                  *(dp++) = *(sp++);
               }
            }
         }
         else
#endif
         {
            png_bytep sp = row;
            png_bytep dp = row;
            png_uint_32 i;

            for (i = 0; i < row_width; i++)
            {
               png_uint_16 red, green, blue, gray16;
               png_byte hi,lo;

               hi=*(sp)++; lo=*(sp)++; red   = (png_uint_16)((hi << 8) | (lo));
               hi=*(sp)++; lo=*(sp)++; green = (png_uint_16)((hi << 8) | (lo));
               hi=*(sp)++; lo=*(sp)++; blue  = (png_uint_16)((hi << 8) | (lo));

               if (red != green || red != blue)
                  rgb_error |= 1;

               /* From 1.5.5 in the 16 bit case do the accurate conversion even
                * in the 'fast' case - this is because this is where the code
                * ends up when handling linear 16 bit data.
                */
               gray16  = (png_uint_16)((rc*red + gc*green + bc*blue + 16384) >>
                  15);
               *(dp++) = (png_byte)((gray16 >> 8) & 0xff);
               *(dp++) = (png_byte)(gray16 & 0xff);

               if (have_alpha != 0)
               {
                  *(dp++) = *(sp++);
                  *(dp++) = *(sp++);
               }
            }
         }
