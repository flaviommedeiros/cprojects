#ifdef SDL_JOYSTICK_DINPUT
if ( SDL_SYS_IsXInputDeviceIndex(device_index) && s_pXInputMapping )
    {
        return s_pXInputMapping;
    }
    else
#endif
    {
        SDL_JoystickGUID jGUID = SDL_JoystickGetDeviceGUID( device_index );
        return SDL_PrivateGetControllerMappingForGUID(&jGUID);
    }
