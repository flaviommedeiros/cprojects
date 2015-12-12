#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_table != NULL)
                  {
                     sp = row;
                     for (i = 0; i < row_width; i++, sp++)
                     {
                        if (*sp == trans_color->gray)
                        {
                           *sp = (png_byte)background->gray;
                        }
                        else
                        {
                           *sp = gamma_table[*sp];
                        }
                     }
                  }
                  else
#endif
                  {
                     sp = row;
                     for (i = 0; i < row_width; i++, sp++)
                     {
                        if (*sp == trans_color->gray)
                        {
                           *sp = (png_byte)background->gray;
                        }
                     }
                  }
