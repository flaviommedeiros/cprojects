#ifdef PNG_READ_GAMMA_SUPPORTED
if (gamma_table != NULL)
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 3)
                  {
                     if (*sp == png_ptr->trans_color.red &&
                         *(sp + 1) == png_ptr->trans_color.green &&
                         *(sp + 2) == png_ptr->trans_color.blue)
                     {
                        *sp = (png_byte)png_ptr->background.red;
                        *(sp + 1) = (png_byte)png_ptr->background.green;
                        *(sp + 2) = (png_byte)png_ptr->background.blue;
                     }

                     else
                     {
                        *sp = gamma_table[*sp];
                        *(sp + 1) = gamma_table[*(sp + 1)];
                        *(sp + 2) = gamma_table[*(sp + 2)];
                     }
                  }
               }
               else
#endif
               {
                  sp = row;
                  for (i = 0; i < row_width; i++, sp += 3)
                  {
                     if (*sp == png_ptr->trans_color.red &&
                         *(sp + 1) == png_ptr->trans_color.green &&
                         *(sp + 2) == png_ptr->trans_color.blue)
                     {
                        *sp = (png_byte)png_ptr->background.red;
                        *(sp + 1) = (png_byte)png_ptr->background.green;
                        *(sp + 2) = (png_byte)png_ptr->background.blue;
                     }
                  }
               }
