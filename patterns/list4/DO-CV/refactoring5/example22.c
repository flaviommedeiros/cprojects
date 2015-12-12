#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL && gamma_16_from_1 != NULL &&
                   gamma_16_to_1 != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 4)
                  {
                     png_uint_16 a = (png_uint_16)(((*(sp + 2)) << 8)
                         + *(sp + 3));

                     if (a == (png_uint_16)0xffff)
                     {
                        png_uint_16 v;

                        v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                        *sp = (png_byte)((v >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(v & 0xff);
                     }

                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *sp = (png_byte)((png_ptr->background.gray >> 8)
                                & 0xff);
                        *(sp + 1) = (png_byte)(png_ptr->background.gray & 0xff);
                     }

                     else
                     {
                        png_uint_16 g, v, w;

                        g = gamma_16_to_1[*(sp + 1) >> gamma_shift][*sp];
                        png_composite_16(v, g, a, png_ptr->background_1.gray);
                        if (optimize)
                           w = v;
                        else
                           w = gamma_16_from_1[(v&0xff) >> gamma_shift][v >> 8];
                        *sp = (png_byte)((w >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(w & 0xff);
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 4)
                  {
                     png_uint_16 a = (png_uint_16)(((*(sp + 2)) << 8)
                         + *(sp + 3));

                     if (a == 0)
                     {
                        *sp = (png_byte)((png_ptr->background.gray >> 8)
                                & 0xff);
                        *(sp + 1) = (png_byte)(png_ptr->background.gray & 0xff);
                     }

                     else if (a < 0xffff)
                     {
                        png_uint_16 g, v;

                        g = (png_uint_16)(((*sp) << 8) + *(sp + 1));
                        png_composite_16(v, g, a, png_ptr->background.gray);
                        *sp = (png_byte)((v >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(v & 0xff);
                     }
                  }
               }
