#ifdef ALDRIVER_ALT
if( !QAL_Init( ALDRIVER_ALT, verbose ) )
#endif
		{
			Com_Printf( "Failed to load OpenAL library: %s\n", ALDRIVER );
			return false;
		}
