if ((
#ifdef PNG_READ_INTERLACING_SUPPORTED
             png_ptr->interlaced && png_ptr->pass > 6) ||
             (!png_ptr->interlaced &&
#endif
             png_ptr->row_number == png_ptr->num_rows))
         {
           if (png_ptr->zstream.avail_in)
             png_warning(png_ptr, "Too much data in IDAT chunks");
           png_ptr->flags |= PNG_FLAG_ZLIB_FINISHED;
           break;
         }
