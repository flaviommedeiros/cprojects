switch (fourcc) {
      case MKFOURCC('V', 'P', '8', 'X'): {
        return PARSE_ERROR;
      }
      case MKFOURCC('A', 'L', 'P', 'H'):
      case MKFOURCC('V', 'P', '8', ' '):
      case MKFOURCC('V', 'P', '8', 'L'): {
        // check that this isn't an animation (all frames should be in an ANMF).
        if (anim_chunks > 0 || is_animation) return PARSE_ERROR;

        Rewind(mem, CHUNK_HEADER_SIZE);
        status = ParseSingleImage(dmux);
        break;
      }
      case MKFOURCC('A', 'N', 'I', 'M'): {
        if (chunk_size_padded < ANIM_CHUNK_SIZE) return PARSE_ERROR;

        if (MemDataSize(mem) < chunk_size_padded) {
          status = PARSE_NEED_MORE_DATA;
        } else if (anim_chunks == 0) {
          ++anim_chunks;
          dmux->bgcolor_ = ReadLE32(mem);
          dmux->loop_count_ = ReadLE16s(mem);
          Skip(mem, chunk_size_padded - ANIM_CHUNK_SIZE);
        } else {
          store_chunk = 0;
          goto Skip;
        }
        break;
      }
      case MKFOURCC('A', 'N', 'M', 'F'): {
        if (anim_chunks == 0) return PARSE_ERROR;  // 'ANIM' precedes frames.
        status = ParseAnimationFrame(dmux, chunk_size_padded);
        break;
      }
#ifdef WEBP_EXPERIMENTAL_FEATURES
      case MKFOURCC('F', 'R', 'G', 'M'): {
        status = ParseFragment(dmux, chunk_size_padded);
        break;
      }
#endif
      case MKFOURCC('I', 'C', 'C', 'P'): {
        store_chunk = !!(dmux->feature_flags_ & ICCP_FLAG);
        goto Skip;
      }
      case MKFOURCC('E', 'X', 'I', 'F'): {
        store_chunk = !!(dmux->feature_flags_ & EXIF_FLAG);
        goto Skip;
      }
      case MKFOURCC('X', 'M', 'P', ' '): {
        store_chunk = !!(dmux->feature_flags_ & XMP_FLAG);
        goto Skip;
      }
 Skip:
      default: {
        if (chunk_size_padded <= MemDataSize(mem)) {
          if (store_chunk) {
            // Store only the chunk header and unpadded size as only the payload
            // will be returned to the user.
            if (!StoreChunk(dmux, chunk_start_offset,
                            CHUNK_HEADER_SIZE + chunk_size)) {
              return PARSE_ERROR;
            }
          }
          Skip(mem, chunk_size_padded);
        } else {
          status = PARSE_NEED_MORE_DATA;
        }
      }
    }
