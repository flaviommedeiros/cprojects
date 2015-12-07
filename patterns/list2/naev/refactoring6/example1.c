if (((key == SDLK_NUMLOCK) ||
                  (key == SDLK_CAPSLOCK) ||
                  (key == SDLK_SCROLLOCK) ||
                  (key == SDLK_RSHIFT) ||
                  (key == SDLK_LSHIFT) ||
                  (key == SDLK_RCTRL) ||
                  (key == SDLK_LCTRL) ||
                  (key == SDLK_RALT) ||
                  (key == SDLK_LALT) ||
#if !SDL_VERSION_ATLEAST(2,0,0) /* SUPER don't exist in 2.0.0 */
                  (key == SDLK_LSUPER) ||
                  (key == SDLK_RSUPER) ||
#endif /* !SDL_VERSION_ATLEAST(2,0,0) */
                  (key == SDLK_RMETA) ||
                  (key == SDLK_LMETA))
                  && (opt_lastKeyPress != key)) {
            opt_lastKeyPress = key;
            return 0;
         }
