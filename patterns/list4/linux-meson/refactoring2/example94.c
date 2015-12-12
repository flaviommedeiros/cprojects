#ifdef CONFIG_LINE6_USB_IMPULSE_RESPONSE
if (!(line6pcm->flags & LINE6_BITS_PCM_IMPULSE))
#endif
			if (test_bit(LINE6_INDEX_PCM_ALSA_CAPTURE_STREAM,
				     &line6pcm->flags))
				line6_capture_check_period(line6pcm, length);
