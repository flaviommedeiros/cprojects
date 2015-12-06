switch (bit_depth)
         {
            case 1:
            case 2:
            case 4:
            case 8:
#ifdef PNG_WRITE_16BIT_SUPPORTED
            case 16:
#endif
               png_ptr->channels = 1; break;

            default:
               png_error(png_ptr,
                   "Invalid bit depth for grayscale image");
         }
