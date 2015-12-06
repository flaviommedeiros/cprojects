static videoDecode_t videoDecoders[] =
{
	{ "\0",  "\0",  NULL,     NULL, NULL,          NULL,                NULL,      NULL          },
	{ "roq", "\0",  ROQ_Init, NULL, ROQ_StartRead, ROQ_UpdateCinematic, ROQ_Reset, ROQ_StopVideo },
#ifdef FEATURE_THEORA
	{ "ogv", "ogm", NULL,     NULL, OGV_StartRead, OGV_UpdateCinematic, NULL,      OGV_StopVideo },
#endif
};
