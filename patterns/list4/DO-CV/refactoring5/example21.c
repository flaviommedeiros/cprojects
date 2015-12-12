#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_to_1 != NULL && gamma_from_1 != NULL &&
                   gamma_table != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 2)
                  {
                     png_uint_16 a = *(sp + 1);

                     if (a == 0xff)
                        *sp = gamma_table[*sp];

                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *sp = (png_byte)png_ptr->background.gray;
                     }

                     else
                     {
                        png_byte v, w;

                        v = gamma_to_1[*sp];
                        png_composite(w, v, a, png_ptr->background_1.gray);
                        if (!optimize)
                           w = gamma_from_1[w];
                        *sp = w;
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 2)
                  {
                     png_byte a = *(sp + 1);

                     if (a == 0)
                        *sp = (png_byte)png_ptr->background.gray;

                     else if (a < 0xff)
                        png_composite(*sp, *sp, a, png_ptr->background.gray);
                  }
               }
