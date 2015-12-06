#ifdef __APPLE__
if (qalcCaptureOpenDevice == NULL)
#else
		if (!qalcIsExtensionPresent(NULL, "ALC_EXT_capture"))
#endif
		{
			Com_Printf("No ALC_EXT_capture support, can't record audio.\n");
		}
		else
		{
			// !!! FIXME: 8000Hz is what Speex narrowband mode needs, but we
			// !!! FIXME:  should probably open the capture device after
			// !!! FIXME:  initializing Speex so we can change to wideband
			// !!! FIXME:  if we like.
			Com_Printf("OpenAL default capture device is '%s'\n",
			           qalcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER));
			alCaptureDevice = qalcCaptureOpenDevice(NULL, 8000, AL_FORMAT_MONO16, 4096);
			Com_Printf("OpenAL capture device %s.\n",
			           (alCaptureDevice == NULL) ? "failed to open" : "opened");
		}
