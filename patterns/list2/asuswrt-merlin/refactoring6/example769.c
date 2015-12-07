if(!
		EncoderSession_construct(
			&encoder_session,
#if FLAC__HAS_OGG
			options.common.use_ogg,
#else
			/*use_ogg=*/false,
#endif
			options.common.verify,
			options.common.treat_warnings_as_errors,
			options.common.continue_through_decode_errors,
			infile,
			infilename,
			outfilename
		)
	)
		return 1;
