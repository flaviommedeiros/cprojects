if(!
		DecoderSession_construct(
			&decoder_session,
#if FLAC__HAS_OGG
			options.common.is_ogg,
			options.common.use_first_serial_number,
			options.common.serial_number,
#else
			/*is_ogg=*/false,
			/*use_first_serial_number=*/false,
			/*serial_number=*/0,
#endif
			/*is_aiff_out=*/false,
			/*is_wave_out=*/true,
			options.common.treat_warnings_as_errors,
			options.common.continue_through_decode_errors,
			options.common.channel_map_none,
			options.common.replaygain_synthesis_spec,
			analysis_mode,
			aopts,
			&options.common.skip_specification,
			&options.common.until_specification,
			options.common.has_cue_specification? &options.common.cue_specification : 0,
			options.foreign_metadata,
			infilename,
			outfilename
		)
	)
		return 1;
