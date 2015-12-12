#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_to_1 != NULL && gamma_from_1 != NULL &&
                   gamma_table != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 4)
                  {
                     png_byte a = *(sp + 3);

                     if (a == 0xff)
                     {
                        *sp = gamma_table[*sp];
                        *(sp + 1) = gamma_table[*(sp + 1)];
                        *(sp + 2) = gamma_table[*(sp + 2)];
                     }

                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *sp = (png_byte)png_ptr->background.red;
                        *(sp + 1) = (png_byte)png_ptr->background.green;
                        *(sp + 2) = (png_byte)png_ptr->background.blue;
                     }

                     else
                     {
                        png_byte v, w;

                        v = gamma_to_1[*sp];
                        png_composite(w, v, a, png_ptr->background_1.red);
                        if (optimize == 0) w = gamma_from_1[w];
                        *sp = w;

                        v = gamma_to_1[*(sp + 1)];
                        png_composite(w, v, a, png_ptr->background_1.green);
                        if (optimize == 0) w = gamma_from_1[w];
                        *(sp + 1) = w;

                        v = gamma_to_1[*(sp + 2)];
                        png_composite(w, v, a, png_ptr->background_1.blue);
                        if (optimize == 0) w = gamma_from_1[w];
                        *(sp + 2) = w;
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 4)
                  {
                     png_byte a = *(sp + 3);

                     if (a == 0)
                     {
                        *sp = (png_byte)png_ptr->background.red;
                        *(sp + 1) = (png_byte)png_ptr->background.green;
                        *(sp + 2) = (png_byte)png_ptr->background.blue;
                     }

                     else if (a < 0xff)
                     {
                        png_composite(*sp, *sp, a, png_ptr->background.red);

                        png_composite(*(sp + 1), *(sp + 1), a,
                            png_ptr->background.green);

                        png_composite(*(sp + 2), *(sp + 2), a,
                            png_ptr->background.blue);
                     }
                  }
               }
