#if SDL_VERSION_ATLEAST(2,0,0)
if ( SDL_PERCORE_JOYSTICKS[ i ].mJoystick )
#else
			if ( SDL_JoystickOpened( i ) )
#endif
         {
            SDL_JoystickClose( SDL_PERCORE_JOYSTICKS[ i ].mJoystick );

            free( SDL_PERCORE_JOYSTICKS[ i ].mScanStatus );
            free( SDL_PERCORE_JOYSTICKS[ i ].mHatStatus );
         }
