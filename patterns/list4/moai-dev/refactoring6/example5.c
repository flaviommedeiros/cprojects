if (png_handle_as_unknown(png_ptr, png_ptr->chunk_name) !=
         PNG_HANDLE_CHUNK_ALWAYS
#ifdef PNG_READ_USER_CHUNKS_SUPPORTED
         && png_ptr->read_user_chunk_fn == NULL
#endif
         )
#endif
         png_chunk_error(png_ptr, "unknown critical chunk");
