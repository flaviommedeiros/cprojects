#ifdef PNG_READ_EXPAND_SUPPORTED
if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
#endif
           {
           /* Invert the alpha channel (in tRNS) unless the pixels are
            * going to be expanded, in which case leave it for later
            */
              int i, istop;
              istop=(int)png_ptr->num_trans;
              for (i=0; i<istop; i++)
                 png_ptr->trans_alpha[i] = (png_byte)(255 - png_ptr->trans_alpha[i]);
           }
