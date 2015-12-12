#ifdef PNG_WARNINGS_SUPPORTED
if (warn)
             png_chunk_warning(png_ptr, "insufficient memory to read chunk");
         else
#endif
         {
#ifdef PNG_ERROR_TEXT_SUPPORTED
             png_chunk_error(png_ptr, "insufficient memory to read chunk");
#endif
         }
