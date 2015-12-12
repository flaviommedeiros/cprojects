if (! ONIGENC_IS_MBC_NEWLINE(reg->enc, p, end)
#ifdef USE_CRNL_AS_LINE_TERMINATOR
              && ! ONIGENC_IS_MBC_CRNL(reg->enc, p, end)
#endif
                ) {
	  p = onigenc_get_prev_char_head(reg->enc, adjrange, p);
	  if (IS_NULL(p)) goto fail;
	  goto retry;
	}
