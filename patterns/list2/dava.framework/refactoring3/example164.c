switch (id) {
      case WEBP_CHUNK_ALPHA:
        if (wpi->alpha_ != NULL) goto Err;  // Consecutive ALPH chunks.
        if (ChunkSetNth(&chunk, &wpi->alpha_, 1) != WEBP_MUX_OK) goto Err;
        wpi->is_partial_ = 1;  // Waiting for a VP8 chunk.
        break;
      case WEBP_CHUNK_IMAGE:
        if (ChunkSetNth(&chunk, &wpi->img_, 1) != WEBP_MUX_OK) goto Err;
        if (!MuxImageFinalize(wpi)) goto Err;
        wpi->is_partial_ = 0;  // wpi is completely filled.
 PushImage:
        // Add this to mux->images_ list.
        if (MuxImagePush(wpi, &mux->images_) != WEBP_MUX_OK) goto Err;
        MuxImageInit(wpi);  // Reset for reading next image.
        break;
      case WEBP_CHUNK_ANMF:
#ifdef WEBP_EXPERIMENTAL_FEATURES
      case WEBP_CHUNK_FRGM:
#endif
        if (wpi->is_partial_) goto Err;  // Previous wpi is still incomplete.
        if (!MuxImageParse(&chunk, copy_data, wpi)) goto Err;
        ChunkRelease(&chunk);
        goto PushImage;
        break;
      default:  // A non-image chunk.
        if (wpi->is_partial_) goto Err;  // Encountered a non-image chunk before
                                         // getting all chunks of an image.
        chunk_list = MuxGetChunkListFromId(mux, id);  // List to add this chunk.
        if (ChunkSetNth(&chunk, chunk_list, 0) != WEBP_MUX_OK) goto Err;
        if (id == WEBP_CHUNK_VP8X) {  // grab global specs
          mux->canvas_width_ = GetLE24(data + 12) + 1;
          mux->canvas_height_ = GetLE24(data + 15) + 1;
        }
        break;
    }
