#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_to_1 != NULL && gamma_from_1 != NULL &&
                   gamma_table != NULL)
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 2, dp++)
                  {
                     png_uint_16 a = *(sp + 1);

                     if (a == 0xff)
                     {
                        *dp = gamma_table[*sp];
                     }
                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *dp = (png_byte)background->gray;
                     }
                     else
                     {
                        png_byte v, w;

                        v = gamma_to_1[*sp];
                        png_composite(w, v, a, background_1->gray);
                        *dp = gamma_from_1[w];
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 2, dp++)
                  {
                     png_byte a = *(sp + 1);

                     if (a == 0xff)
                     {
                        *dp = *sp;
                     }
#ifdef PNG_READ_GAMMA_SUPPORTED
                     else if (a == 0)
                     {
                        *dp = (png_byte)background->gray;
                     }
                     else
                     {
                        png_composite(*dp, *sp, a, background_1->gray);
                     }
#else
                     *dp = (png_byte)background->gray;
#endif
                  }
               }
