#        ifdef PNG_READ_PACKSWAP_SUPPORTED
if ((png_ptr->transformations & PNG_PACKSWAP) != 0)
               mask = MASK(pass, pixel_depth, display, 0);

            else
#        endif
            mask = MASK(pass, pixel_depth, display, 1);
