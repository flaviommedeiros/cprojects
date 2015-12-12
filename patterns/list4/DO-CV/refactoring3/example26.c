switch (filters & (PNG_ALL_FILTERS | 0x07))
      {
#ifdef PNG_WRITE_FILTER_SUPPORTED
         case 5:
         case 6:
         case 7: png_app_error(png_ptr, "Unknown row filter for method 0");
            /* FALL THROUGH */
#endif /* PNG_WRITE_FILTER_SUPPORTED */
         case PNG_FILTER_VALUE_NONE:
            png_ptr->do_filter = PNG_FILTER_NONE; break;

#ifdef PNG_WRITE_FILTER_SUPPORTED
         case PNG_FILTER_VALUE_SUB:
            png_ptr->do_filter = PNG_FILTER_SUB; break;

         case PNG_FILTER_VALUE_UP:
            png_ptr->do_filter = PNG_FILTER_UP; break;

         case PNG_FILTER_VALUE_AVG:
            png_ptr->do_filter = PNG_FILTER_AVG; break;

         case PNG_FILTER_VALUE_PAETH:
            png_ptr->do_filter = PNG_FILTER_PAETH; break;

         default:
            png_ptr->do_filter = (png_byte)filters; break;
#else
         default:
            png_app_error(png_ptr, "Unknown row filter for method 0");
#endif /* PNG_WRITE_FILTER_SUPPORTED */
      }
