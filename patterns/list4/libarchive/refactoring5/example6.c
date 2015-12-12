#ifdef HAVE_LZMA_STREAM_ENCODER_MT
if (threads > 1) {
		bzero(&mt_options, sizeof(mt_options));
		mt_options.threads = threads;
		mt_options.timeout = 300;
		mt_options.filters = lzmafilters;
		mt_options.check = LZMA_CHECK_CRC64;
		r = lzma_stream_encoder_mt(strm, &mt_options);
	} else
#endif
		r = lzma_stream_encoder(strm, lzmafilters, LZMA_CHECK_CRC64);
