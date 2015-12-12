#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL && gamma_16_from_1 != NULL &&
                   gamma_16_to_1 != NULL)
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 4, dp += 2)
                  {
                     png_uint_16 a = (png_uint_16)(((*(sp+2)) << 8) + *(sp+3));

                     if (a == (png_uint_16)0xffff)
                     {
                        png_uint_16 v;

                        v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                        *dp = (png_byte)((v >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(v & 0xff);
                     }
#ifdef PNG_READ_GAMMA_SUPPORTED
                     else if (a == 0)
#else
                     else
#endif
                     {
                        /* Background is already in screen gamma */
                        *dp = (png_byte)((background->gray >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(background->gray & 0xff);
                     }
#ifdef PNG_READ_GAMMA_SUPPORTED
                     else
                     {
                        png_uint_16 g, v, w;

                        g = gamma_16_to_1[*(sp + 1) >> gamma_shift][*sp];
                        png_composite_16(v, g, a, background_1->gray);
                        w = gamma_16_from_1[(v&0xff) >> gamma_shift][v >> 8];
                        *dp = (png_byte)((w >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(w & 0xff);
                     }
#endif
                  }
               }
               else
#endif
               {
                  sp = row;
                  dp = row;
                  for (i = 0; i < row_width; i++, sp += 4, dp += 2)
                  {
                     png_uint_16 a = (png_uint_16)(((*(sp+2)) << 8) + *(sp+3));
                     if (a == (png_uint_16)0xffff)
                     {
                        png_memcpy(dp, sp, 2);
                     }
#ifdef PNG_READ_GAMMA_SUPPORTED
                     else if (a == 0)
#else
                     else
#endif
                     {
                        *dp = (png_byte)((background->gray >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(background->gray & 0xff);
                     }
#ifdef PNG_READ_GAMMA_SUPPORTED
                     else
                     {
                        png_uint_16 g, v;

                        g = (png_uint_16)(((*sp) << 8) + *(sp + 1));
                        png_composite_16(v, g, a, background_1->gray);
                        *dp = (png_byte)((v >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(v & 0xff);
                     }
#endif
                  }
               }
