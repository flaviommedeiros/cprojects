switch (state)
         {
#           ifdef PNG_WRITE_COMPRESSED_TEXT_SUPPORTED
               case PNG_ZLIB_FOR_TEXT:
                  ret = deflateInit2(&png_ptr->zstream,
                     png_ptr->zlib_text_level, png_ptr->zlib_text_method,
                     png_ptr->zlib_text_window_bits,
                     png_ptr->zlib_text_mem_level, png_ptr->zlib_text_strategy);
                  who = "text";
                  break;
#           endif

            case PNG_ZLIB_FOR_IDAT:
               ret = deflateInit2(&png_ptr->zstream, png_ptr->zlib_level,
                   png_ptr->zlib_method, png_ptr->zlib_window_bits,
                   png_ptr->zlib_mem_level, png_ptr->zlib_strategy);
               who = "IDAT";
               break;

            default:
               png_error(png_ptr, "invalid zlib state");
         }
