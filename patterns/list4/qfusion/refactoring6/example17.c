if ((saveme->format->BitsPerPixel == 24) &&
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                   (saveme->format->Rmask == 0x00FF0000) &&
                   (saveme->format->Gmask == 0x0000FF00) &&
                   (saveme->format->Bmask == 0x000000FF)
#else
                   (saveme->format->Rmask == 0x000000FF) &&
                   (saveme->format->Gmask == 0x0000FF00) &&
                   (saveme->format->Bmask == 0x00FF0000)
#endif
            ) {
            surface = saveme;
        } else {
            SDL_PixelFormat format;

            /* If the surface has a colorkey or alpha channel we'll save a
               32-bit BMP with alpha channel, otherwise save a 24-bit BMP. */
            if (save32bit) {
                SDL_InitFormat(&format,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                               SDL_PIXELFORMAT_ARGB8888
#else
                               SDL_PIXELFORMAT_BGRA8888
#endif
                               );
            } else {
                SDL_InitFormat(&format, SDL_PIXELFORMAT_BGR24);
            }
            surface = SDL_ConvertSurface(saveme, &format, 0);
            if (!surface) {
                SDL_SetError("Couldn't convert image to %d bpp",
                             format.BitsPerPixel);
            }
        }
