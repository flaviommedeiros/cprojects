#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 6)
                  {
                     png_uint_16 r = (png_uint_16)(((*sp) << 8) + *(sp + 1));

                     png_uint_16 g = (png_uint_16)(((*(sp + 2)) << 8)
                         + *(sp + 3));

                     png_uint_16 b = (png_uint_16)(((*(sp + 4)) << 8)
                         + *(sp + 5));

                     if (r == png_ptr->trans_color.red &&
                         g == png_ptr->trans_color.green &&
                         b == png_ptr->trans_color.blue)
                     {
                        /* Background is already in screen gamma */
                        *sp = (png_byte)((png_ptr->background.red >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(png_ptr->background.red & 0xff);
                        *(sp + 2) = (png_byte)((png_ptr->background.green >> 8)
                                & 0xff);
                        *(sp + 3) = (png_byte)(png_ptr->background.green
                                & 0xff);
                        *(sp + 4) = (png_byte)((png_ptr->background.blue >> 8)
                                & 0xff);
                        *(sp + 5) = (png_byte)(png_ptr->background.blue & 0xff);
                     }

                     else
                     {
                        png_uint_16 v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                        *sp = (png_byte)((v >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(v & 0xff);

                        v = gamma_16[*(sp + 3) >> gamma_shift][*(sp + 2)];
                        *(sp + 2) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 3) = (png_byte)(v & 0xff);

                        v = gamma_16[*(sp + 5) >> gamma_shift][*(sp + 4)];
                        *(sp + 4) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 5) = (png_byte)(v & 0xff);
                     }
                  }
               }

               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 6)
                  {
                     png_uint_16 r = (png_uint_16)(((*sp) << 8) + *(sp + 1));

                     png_uint_16 g = (png_uint_16)(((*(sp + 2)) << 8)
                         + *(sp + 3));

                     png_uint_16 b = (png_uint_16)(((*(sp + 4)) << 8)
                         + *(sp + 5));

                     if (r == png_ptr->trans_color.red &&
                         g == png_ptr->trans_color.green &&
                         b == png_ptr->trans_color.blue)
                     {
                        *sp = (png_byte)((png_ptr->background.red >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(png_ptr->background.red & 0xff);
                        *(sp + 2) = (png_byte)((png_ptr->background.green >> 8)
                                & 0xff);
                        *(sp + 3) = (png_byte)(png_ptr->background.green
                                & 0xff);
                        *(sp + 4) = (png_byte)((png_ptr->background.blue >> 8)
                                & 0xff);
                        *(sp + 5) = (png_byte)(png_ptr->background.blue & 0xff);
                     }
                  }
               }
