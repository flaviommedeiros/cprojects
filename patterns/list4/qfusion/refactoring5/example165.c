#ifdef PNG_UNKNOWN_CHUNKS_SUPPORTED
if (png_ptr->unknown_chunk.data)
   {
      png_free(png_ptr, png_ptr->unknown_chunk.data);
      png_ptr->unknown_chunk.data = NULL;
   }
