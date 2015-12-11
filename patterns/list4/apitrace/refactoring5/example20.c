#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL && gamma_16_from_1 != NULL &&
                   gamma_16_to_1 != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 8)
                  {
                     png_uint_16 a = (png_uint_16)(((png_uint_16)(*(sp + 6))
                         << 8) + (png_uint_16)(*(sp + 7)));

                     if (a == (png_uint_16)0xffff)
                     {
                        png_uint_16 v;

                        v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                        *sp = (png_byte)((v >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(v & 0xff);

                        v = gamma_16[*(sp + 3) >> gamma_shift][*(sp + 2)];
                        *(sp + 2) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 3) = (png_byte)(v & 0xff);

                        v = gamma_16[*(sp + 5) >> gamma_shift][*(sp + 4)];
                        *(sp + 4) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 5) = (png_byte)(v & 0xff);
                     }

                     else if (a == 0)
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
                        png_uint_16 v, w;

                        v = gamma_16_to_1[*(sp + 1) >> gamma_shift][*sp];
                        png_composite_16(w, v, a, png_ptr->background_1.red);
                        if (optimize == 0)
                           w = gamma_16_from_1[((w & 0xff) >> gamma_shift)][w >>
                                8];
                        *sp = (png_byte)((w >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(w & 0xff);

                        v = gamma_16_to_1[*(sp + 3) >> gamma_shift][*(sp + 2)];
                        png_composite_16(w, v, a, png_ptr->background_1.green);
                        if (optimize == 0)
                           w = gamma_16_from_1[((w & 0xff) >> gamma_shift)][w >>
                                8];

                        *(sp + 2) = (png_byte)((w >> 8) & 0xff);
                        *(sp + 3) = (png_byte)(w & 0xff);

                        v = gamma_16_to_1[*(sp + 5) >> gamma_shift][*(sp + 4)];
                        png_composite_16(w, v, a, png_ptr->background_1.blue);
                        if (optimize == 0)
                           w = gamma_16_from_1[((w & 0xff) >> gamma_shift)][w >>
                                8];

                        *(sp + 4) = (png_byte)((w >> 8) & 0xff);
                        *(sp + 5) = (png_byte)(w & 0xff);
                     }
                  }
               }

               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 8)
                  {
                     png_uint_16 a = (png_uint_16)(((png_uint_16)(*(sp + 6))
                         << 8) + (png_uint_16)(*(sp + 7)));

                     if (a == 0)
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

                     else if (a < 0xffff)
                     {
                        png_uint_16 v;

                        png_uint_16 r = (png_uint_16)(((*sp) << 8) + *(sp + 1));
                        png_uint_16 g = (png_uint_16)(((*(sp + 2)) << 8)
                            + *(sp + 3));
                        png_uint_16 b = (png_uint_16)(((*(sp + 4)) << 8)
                            + *(sp + 5));

                        png_composite_16(v, r, a, png_ptr->background.red);
                        *sp = (png_byte)((v >> 8) & 0xff);
                        *(sp + 1) = (png_byte)(v & 0xff);

                        png_composite_16(v, g, a, png_ptr->background.green);
                        *(sp + 2) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 3) = (png_byte)(v & 0xff);

                        png_composite_16(v, b, a, png_ptr->background.blue);
                        *(sp + 4) = (png_byte)((v >> 8) & 0xff);
                        *(sp + 5) = (png_byte)(v & 0xff);
                     }
                  }
               }
