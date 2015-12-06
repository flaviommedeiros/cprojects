#ifdef FEATURE_AUTOUPDATE
if (!Q_stricmpn(com_errorMessage, "Server is full", 14))
		{
			Com_GetAutoUpdate();
		}
		else
#endif // FEATURE_AUTOUPDATE
		{
			longjmp(abortframe, -1);
		}
