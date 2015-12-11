#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_table != NULL)
                  {
                     sp = row;
                     shift = 4;
                     for (i = 0; i < row_width; i++)
                     {
                        if ((png_uint_16)((*sp >> shift) & 0x0f)
                            == png_ptr->trans_color.gray)
                        {
                           unsigned int tmp = *sp & (0x0f0f >> (4 - shift));
                           tmp |= png_ptr->background.gray << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        else
                        {
                           unsigned int p = (*sp >> shift) & 0x0f;
                           unsigned int g = (gamma_table[p | (p << 4)] >> 4) &
                              0x0f;
                           unsigned int tmp = *sp & (0x0f0f >> (4 - shift));
                           tmp |= g << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        if (shift == 0)
                        {
                           shift = 4;
                           sp++;
                        }

                        else
                           shift -= 4;
                     }
                  }

                  else
#endif
                  {
                     sp = row;
                     shift = 4;
                     for (i = 0; i < row_width; i++)
                     {
                        if ((png_uint_16)((*sp >> shift) & 0x0f)
                            == png_ptr->trans_color.gray)
                        {
                           unsigned int tmp = *sp & (0x0f0f >> (4 - shift));
                           tmp |= png_ptr->background.gray << shift;
                           *sp = (png_byte)(tmp & 0xff);
                        }

                        if (shift == 0)
                        {
                           shift = 4;
                           sp++;
                        }

                        else
                           shift -= 4;
                     }
                  }
