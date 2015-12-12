#if defined(PNG_SET_CHUNK_MALLOC_LIMIT_SUPPORTED) || \
    defined(PNG_USER_CHUNK_MALLOC_MAX)
if (expanded_size > 0)
#else
      if (expanded_size > 0)
#endif
      {
         /* Success (maybe) - really uncompress the chunk. */
         png_size_t new_size = 0;
         png_charp text = (png_charp)png_malloc_warn(png_ptr,
             prefix_size + expanded_size + 1);

         if (text != NULL)
         {
            png_memcpy(text, png_ptr->chunkdata, prefix_size);
            new_size = png_inflate(png_ptr,
                (png_bytep)(png_ptr->chunkdata + prefix_size),
                chunklength - prefix_size,
                (png_bytep)(text + prefix_size), expanded_size);
            text[prefix_size + expanded_size] = 0; /* just in case */

            if (new_size == expanded_size)
            {
               png_free(png_ptr, png_ptr->chunkdata);
               png_ptr->chunkdata = text;
               *newlength = prefix_size + expanded_size;
               return; /* The success return! */
            }

            png_warning(png_ptr, "png_inflate logic error");
            png_free(png_ptr, text);
         }

         else
            png_warning(png_ptr, "Not enough memory to decompress chunk");
      }
