if (encodings[0].type ||
                (encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_HEADERSTRIP &&
#if CONFIG_ZLIB
                 encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_ZLIB &&
#endif
#if CONFIG_BZLIB
                 encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_BZLIB &&
#endif
                 encodings[0].compression.algo != MATROSKA_TRACK_ENCODING_COMP_LZO)) {
                encodings[0].scope = 0;
                av_log(matroska->ctx, AV_LOG_ERROR,
                       "Unsupported encoding type");
            } else if (track->codec_priv.size && encodings[0].scope&2) {
                uint8_t *codec_priv = track->codec_priv.data;
                int offset = matroska_decode_buffer(&track->codec_priv.data,
                                                    &track->codec_priv.size,
                                                    track);
                if (offset < 0) {
                    track->codec_priv.data = NULL;
                    track->codec_priv.size = 0;
                    av_log(matroska->ctx, AV_LOG_ERROR,
                           "Failed to decode codec private data\n");
                } else if (offset > 0) {
                    track->codec_priv.data = av_malloc(track->codec_priv.size + offset);
                    memcpy(track->codec_priv.data,
                           encodings[0].compression.settings.data, offset);
                    memcpy(track->codec_priv.data+offset, codec_priv,
                           track->codec_priv.size);
                    track->codec_priv.size += offset;
                }
                if (codec_priv != track->codec_priv.data)
                    av_free(codec_priv);
            }
