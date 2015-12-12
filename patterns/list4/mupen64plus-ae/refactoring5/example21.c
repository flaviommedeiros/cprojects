#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_to_1 != NULL && gamma_from_1 != NULL &&
                   gamma_table != NULL)
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 4, dp += 3)
                  {
                     png_byte a = *(sp + 3);

                     if (a == 0xff)
                     {
                        *dp = gamma_table[*sp];
                        *(dp + 1) = gamma_table[*(sp + 1)];
                        *(dp + 2) = gamma_table[*(sp + 2)];
                     }
                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *dp = (png_byte)background->red;
                        *(dp + 1) = (png_byte)background->green;
                        *(dp + 2) = (png_byte)background->blue;
                     }
                     else
                     {
                        png_byte v, w;

                        v = gamma_to_1[*sp];
                        png_composite(w, v, a, background_1->red);
                        *dp = gamma_from_1[w];
                        v = gamma_to_1[*(sp + 1)];
                        png_composite(w, v, a, background_1->green);
                        *(dp + 1) = gamma_from_1[w];
                        v = gamma_to_1[*(sp + 2)];
                        png_composite(w, v, a, background_1->blue);
                        *(dp + 2) = gamma_from_1[w];
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 4, dp += 3)
                  {
                     png_byte a = *(sp + 3);

                     if (a == 0xff)
                     {
                        *dp = *sp;
                        *(dp + 1) = *(sp + 1);
                        *(dp + 2) = *(sp + 2);
                     }
                     else if (a == 0)
                     {
                        *dp = (png_byte)background->red;
                        *(dp + 1) = (png_byte)background->green;
                        *(dp + 2) = (png_byte)background->blue;
                     }
                     else
                     {
                        png_composite(*dp, *sp, a, background->red);
                        png_composite(*(dp + 1), *(sp + 1), a,
                           background->green);
                        png_composite(*(dp + 2), *(sp + 2), a,
                           background->blue);
                     }
                  }
               }
