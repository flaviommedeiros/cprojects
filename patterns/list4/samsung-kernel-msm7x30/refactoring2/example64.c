#ifdef CONFIG_LINE6_USB_IMPULSE_RESPONSE
if (!(line6pcm->flags & LINE6_BITS_PCM_IMPULSE))
#endif
			if (test_bit(LINE6_INDEX_PCM_ALSA_CAPTURE_STREAM, &line6pcm->flags)
			    && (fsize > 0))
				line6_capture_copy(line6pcm, fbuf, fsize);
