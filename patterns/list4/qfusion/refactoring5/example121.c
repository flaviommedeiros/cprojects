#ifdef __ANDROID__
if (SDL_NumJoysticks() > 0) {
#else
    if (argv[1]) {
#endif
        SDL_bool reportederror = SDL_FALSE;
        SDL_bool keepGoing = SDL_TRUE;
        SDL_Event event;
        int device;
#ifdef __ANDROID__
        device = 0;
#else
        device = atoi(argv[1]);
#endif
        joystick = SDL_JoystickOpen(device);

        while ( keepGoing ) {
            if (joystick == NULL) {
                if ( !reportederror ) {
                    SDL_Log("Couldn't open joystick %d: %s\n", device, SDL_GetError());
                    keepGoing = SDL_FALSE;
                    reportederror = SDL_TRUE;
                }
            } else {
                reportederror = SDL_FALSE;
                keepGoing = WatchJoystick(joystick);
                SDL_JoystickClose(joystick);
            }

            joystick = NULL;
            if (keepGoing) {
                SDL_Log("Waiting for attach\n");
            }
            while (keepGoing) {
                SDL_WaitEvent(&event);
                if ((event.type == SDL_QUIT) || (event.type == SDL_FINGERDOWN)
                    || (event.type == SDL_MOUSEBUTTONDOWN)) {
                    keepGoing = SDL_FALSE;
                } else if (event.type == SDL_JOYDEVICEADDED) {
                    joystick = SDL_JoystickOpen(device);
                    break;
                }
            }
        }
    }
    else {
        SDL_Log("\n\nUsage: ./controllermap number\nFor example: ./controllermap 0\nOr: ./controllermap 0 >> gamecontrollerdb.txt");
    }
    SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    return 0;
}
