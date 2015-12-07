if(
					status == FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM ||
					(
#if FLAC__HAS_OGG
						/* see [1] HACK NOTE below for why we don't call the eof_callback when decoding Ogg FLAC */
						!decoder->private_->is_ogg &&
#endif
						decoder->private_->eof_callback && decoder->private_->eof_callback(decoder, decoder->private_->client_data)
					)
				) {
					decoder->protected_->state = FLAC__STREAM_DECODER_END_OF_STREAM;
					return false;
				}
				else
					return true;
