#ifndef FEATURE_RENDERER_GLES
if (cls.glconfig.stereoEnabled)
	{
		SCR_DrawScreenField(STEREO_LEFT);
		SCR_DrawScreenField(STEREO_RIGHT);
	}
	else
#endif
	{
		SCR_DrawScreenField(STEREO_CENTER);
	}
