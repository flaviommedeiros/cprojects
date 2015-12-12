#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_table != NULL)
                  {
                     sp = row;
                     shift = 6;
                     for (i = 0; i < row_width; i++)
                     {
                        if ((png_uint_16)((*sp >> shift) & 0x03)
                            == png_ptr->trans_color.gray)
                        {
                           unsigned int tmp = *sp & (0x3f3f >> (6 - shift));
                           tmp |= png_ptr->background.gray << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        else
                        {
                           unsigned int p = (*sp >> shift) & 0x03;
                           unsigned int g = (gamma_table [p | (p << 2) |
                               (p << 4) | (p << 6)] >> 6) & 0x03;
                           unsigned int tmp = *sp & (0x3f3f >> (6 - shift));
                           tmp |= g << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        if (!shift)
                        {
                           shift = 6;
                           sp++;
                        }

                        else
                           shift -= 2;
                     }
                  }

                  else
#endif
                  {
                     sp = row;
                     shift = 6;
                     for (i = 0; i < row_width; i++)
                     {
                        if ((png_uint_16)((*sp >> shift) & 0x03)
                            == png_ptr->trans_color.gray)
                        {
                           unsigned int tmp = *sp & (0x3f3f >> (6 - shift));
                           tmp |= png_ptr->background.gray << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        if (!shift)
                        {
                           shift = 6;
                           sp++;
                        }

                        else
                           shift -= 2;
                     }
                  }
