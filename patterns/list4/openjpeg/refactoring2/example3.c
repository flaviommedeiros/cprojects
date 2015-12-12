#ifdef PNG_SET_UNKNOWN_CHUNKS_SUPPORTED
if (keep != PNG_HANDLE_CHUNK_NEVER &&
             ((up->name[3] & 0x20) /* safe-to-copy overrides everything */ ||
              keep == PNG_HANDLE_CHUNK_ALWAYS ||
              (keep == PNG_HANDLE_CHUNK_AS_DEFAULT &&
               png_ptr->unknown_default == PNG_HANDLE_CHUNK_ALWAYS)))
#endif
         {
            /* TODO: review, what is wrong with a zero length unknown chunk? */
            if (up->size == 0)
               png_warning(png_ptr, "Writing zero-length unknown chunk");

            png_write_chunk(png_ptr, up->name, up->data, up->size);
         }
