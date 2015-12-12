#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_16 != NULL)
                  {
                     sp = row;
                     for (i = 0; i < row_width; i++, sp += 2)
                     {
                        png_uint_16 v;

                        v = (png_uint_16)(((*sp) << 8) + *(sp + 1));

                        if (v == png_ptr->trans_color.gray)
                        {
                           /* Background is already in screen gamma */
                           *sp = (png_byte)((png_ptr->background.gray >> 8) & 0xff);
                           *(sp + 1) = (png_byte)(png_ptr->background.gray & 0xff);
                        }

                        else
                        {
                           v = gamma_16[*(sp + 1) >> gamma_shift][*sp];
                           *sp = (png_byte)((v >> 8) & 0xff);
                           *(sp + 1) = (png_byte)(v & 0xff);
                        }
                     }
                  }
                  else
#endif
                  {
                     sp = row;
                     for (i = 0; i < row_width; i++, sp += 2)
                     {
                        png_uint_16 v;

                        v = (png_uint_16)(((*sp) << 8) + *(sp + 1));

                        if (v == png_ptr->trans_color.gray)
                        {
                           *sp = (png_byte)((png_ptr->background.gray >> 8) & 0xff);
                           *(sp + 1) = (png_byte)(png_ptr->background.gray & 0xff);
                        }
                     }
                  }
