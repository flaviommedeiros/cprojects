#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_table != NULL)
                  {
                     sp = row;
                     shift = 4;
                     for (i = 0; i < row_width; i++)
                     {
                        if ((png_uint_16)((*sp >> shift) & 0x0f)
                            == trans_color->gray)
                        {
                           *sp &= (png_byte)((0xf0f >> (4 - shift)) & 0xff);
                           *sp |= (png_byte)(background->gray << shift);
                        }
                        else
                        {
                           png_byte p = (png_byte)((*sp >> shift) & 0x0f);
                           png_byte g = (png_byte)((gamma_table[p |
                             (p << 4)] >> 4) & 0x0f);
                           *sp &= (png_byte)((0xf0f >> (4 - shift)) & 0xff);
                           *sp |= (png_byte)(g << shift);
                        }
                        if (!shift)
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
                            == trans_color->gray)
                        {
                           *sp &= (png_byte)((0xf0f >> (4 - shift)) & 0xff);
                           *sp |= (png_byte)(background->gray << shift);
                        }
                        if (!shift)
                        {
                           shift = 4;
                           sp++;
                        }
                        else
                           shift -= 4;
                     }
                  }
