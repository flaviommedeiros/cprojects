#if defined(PNG_READ_GAMMA_SUPPORTED)
if (a == 0)
#else
                     else
#endif
                     {
                        *dp = (png_byte)((background->gray >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(background->gray & 0xff);
                     }
#if defined(PNG_READ_GAMMA_SUPPORTED)
                     else
                     {
                        png_uint_16 g, v;

                        g = (png_uint_16)(((*sp) << 8) + *(sp + 1));
                        png_composite_16(v, g, a, background_1->gray);
                        *dp = (png_byte)((v >> 8) & 0xff);
                        *(dp + 1) = (png_byte)(v & 0xff);
                     }
