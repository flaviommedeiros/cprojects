if (prefix_size >= (~(png_size_t)0) - 1 ||
         expanded_size >= (~(png_size_t)0) - 1 - prefix_size
#ifdef PNG_USER_LIMITS_SUPPORTED
         || (png_ptr->user_chunk_malloc_max &&
          (prefix_size + expanded_size >= png_ptr->user_chunk_malloc_max - 1))
#else
         || ((PNG_USER_CHUNK_MALLOC_MAX > 0) &&
          prefix_size + expanded_size >= PNG_USER_CHUNK_MALLOC_MAX - 1)
#endif
         )
         png_warning(png_ptr, "Exceeded size limit while expanding chunk");

      /* If the size is zero either there was an error and a message
       * has already been output (warning) or the size really is zero
       * and we have nothing to do - the code will exit through the
       * error case below.
       */
      else if (expanded_size > 0)
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
