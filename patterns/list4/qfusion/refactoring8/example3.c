static const cin_type_t cin_types[] = 
{
	// Ogg Theora
	{
		THEORA_FILE_EXTENSIONS,
		Theora_Init_CIN,
		Theora_HasOggAudio_CIN,
		Theora_Shutdown_CIN,
		Theora_Reset_CIN,
		Theora_NeedNextFrame_CIN,
#ifdef THEORA_SOFTWARE_YUV2RGB
		Theora_ReadNextFrame_CIN,
#else
		NULL,
#endif
		Theora_ReadNextFrameYUV_CIN
	},

	// RoQ - http://wiki.multimedia.cx/index.php?title=ROQ
	{
		ROQ_FILE_EXTENSIONS,
		RoQ_Init_CIN,
		RoQ_HasOggAudio_CIN,
		RoQ_Shutdown_CIN,
		RoQ_Reset_CIN,
		RoQ_NeedNextFrame_CIN,
		NULL,
		RoQ_ReadNextFrameYUV_CIN
	},

	// NULL safe guard
	{
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	}
};
