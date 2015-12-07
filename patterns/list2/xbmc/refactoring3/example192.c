switch (filters & (PNG_ALL_FILTERS | 0x07))
      {
#ifndef PNG_NO_WRITE_FILTER
         case 5:
         case 6:
         case 7: png_warning(png_ptr, "Unknown row filter for method 0");
#endif /* PNG_NO_WRITE_FILTER */
         case PNG_FILTER_VALUE_NONE:
              png_ptr->do_filter=PNG_FILTER_NONE; break;
#ifndef PNG_NO_WRITE_FILTER
         case PNG_FILTER_VALUE_SUB:
              png_ptr->do_filter=PNG_FILTER_SUB; break;
         case PNG_FILTER_VALUE_UP:
              png_ptr->do_filter=PNG_FILTER_UP; break;
         case PNG_FILTER_VALUE_AVG:
              png_ptr->do_filter=PNG_FILTER_AVG; break;
         case PNG_FILTER_VALUE_PAETH:
              png_ptr->do_filter=PNG_FILTER_PAETH; break;
         default: png_ptr->do_filter = (png_byte)filters; break;
#else
         default: png_warning(png_ptr, "Unknown row filter for method 0");
#endif /* PNG_NO_WRITE_FILTER */
      }
