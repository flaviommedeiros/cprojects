#ifdef HAVE_SDL2
if (sdl_pads[id].haptic)
      SDL_HapticClose(sdl_pads[id].haptic);
