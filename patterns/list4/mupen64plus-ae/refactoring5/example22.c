#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL && gamma_16_from_1 != NULL &&
                   gamma_16_to_1 != NULL)
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 8, dp += 6)
                  {
                     png_uint_16 a = (png_uint_16)(((png_uint_16)(*(sp + 6))
                         << 8) + (png_uint_16)(*(sp + 7)));
                     if (a == (png_uint_16)0xffff)
                     {
                        png_uint_16 v;

                        v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                        *dp = (png_byte)((v >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(v & 0xff);
                        v = gamma_16[*(sp + 3) >> gamma_shift][*(sp + 2)];
                        *(dp + 2) = (png_byte)((v >> 8) & 0xff);
                        *(dp + 3) = (png_byte)(v & 0xff);
                        v = gamma_16[*(sp + 5) >> gamma_shift][*(sp + 4)];
                        *(dp + 4) = (png_byte)((v >> 8) & 0xff);
                        *(dp + 5) = (png_byte)(v & 0xff);
                     }
                     else if (a == 0)
                     {
                        /* Background is already in screen gamma */
                        *dp = (png_byte)((background->red >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(background->red & 0xff);
                        *(dp + 2) = (png_byte)((background->green >> 8) & 0xff);
                        *(dp + 3) = (png_byte)(background->green & 0xff);
                        *(dp + 4) = (png_byte)((background->blue >> 8) & 0xff);
                        *(dp + 5) = (png_byte)(background->blue & 0xff);
                     }
                     else
                     {
                        png_uint_16 v, w, x;

                        v = gamma_16_to_1[*(sp + 1) >> gamma_shift][*sp];
                        png_composite_16(w, v, a, background_1->red);
                        x = gamma_16_from_1[((w&0xff) >> gamma_shift)][w >> 8];
                        *dp = (png_byte)((x >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(x & 0xff);
                        v = gamma_16_to_1[*(sp + 3) >> gamma_shift][*(sp + 2)];
                        png_composite_16(w, v, a, background_1->green);
                        x = gamma_16_from_1[((w&0xff) >> gamma_shift)][w >> 8];
                        *(dp + 2) = (png_byte)((x >> 8) & 0xff);
                        *(dp + 3) = (png_byte)(x & 0xff);
                        v = gamma_16_to_1[*(sp + 5) >> gamma_shift][*(sp + 4)];
                        png_composite_16(w, v, a, background_1->blue);
                        x = gamma_16_from_1[(w & 0xff) >> gamma_shift][w >> 8];
                        *(dp + 4) = (png_byte)((x >> 8) & 0xff);
                        *(dp + 5) = (png_byte)(x & 0xff);
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 8, dp += 6)
                  {
                     png_uint_16 a = (png_uint_16)(((png_uint_16)(*(sp + 6))
                        << 8) + (png_uint_16)(*(sp + 7)));
                     if (a == (png_uint_16)0xffff)
                     {
                        png_memcpy(dp, sp, 6);
                     }
                     else if (a == 0)
                     {
                        *dp = (png_byte)((background->red >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(background->red & 0xff);
                        *(dp + 2) = (png_byte)((background->green >> 8) & 0xff);
                        *(dp + 3) = (png_byte)(background->green & 0xff);
                        *(dp + 4) = (png_byte)((background->blue >> 8) & 0xff);
                        *(dp + 5) = (png_byte)(background->blue & 0xff);
                     }
                     else
                     {
                        png_uint_16 v;

                        png_uint_16 r = (png_uint_16)(((*sp) << 8) + *(sp + 1));
                        png_uint_16 g = (png_uint_16)(((*(sp + 2)) << 8)
                            + *(sp + 3));
                        png_uint_16 b = (png_uint_16)(((*(sp + 4)) << 8)
                            + *(sp + 5));

                        png_composite_16(v, r, a, background->red);
                        *dp = (png_byte)((v >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(v & 0xff);
                        png_composite_16(v, g, a, background->green);
                        *(dp + 2) = (png_byte)((v >> 8) & 0xff);
                        *(dp + 3) = (png_byte)(v & 0xff);
                        png_composite_16(v, b, a, background->blue);
                        *(dp + 4) = (png_byte)((v >> 8) & 0xff);
                        *(dp + 5) = (png_byte)(v & 0xff);
                     }
                  }
               }
