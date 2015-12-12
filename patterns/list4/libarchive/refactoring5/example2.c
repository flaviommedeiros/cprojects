#ifdef HAVE_LZMA_STREAM_ENCODER_MT
if (data->threads != 1) {
			bzero(&mt_options, sizeof(mt_options));
			mt_options.threads = data->threads;
			mt_options.timeout = 300;
			mt_options.filters = data->lzmafilters;
			mt_options.check = LZMA_CHECK_CRC64;
			ret = lzma_stream_encoder_mt(&(data->stream),
			    &mt_options);
		} else
#endif
			ret = lzma_stream_encoder(&(data->stream),
			    data->lzmafilters, LZMA_CHECK_CRC64);
