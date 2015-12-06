#ifdef HAVE_SDL2
while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_WINDOWEVENT) > 0)
#else
   while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUITMASK|SDL_VIDEORESIZEMASK) > 0)
#endif
   {
      switch (event.type)
      {
         case SDL_QUIT:
#ifdef HAVE_SDL2
         case SDL_APP_TERMINATING:
#endif
            *quit = true;
            break;
#ifdef HAVE_SDL2
         case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
               sdl->g_resized = true;
               sdl->g_new_width  = event.window.data1;
               sdl->g_new_height = event.window.data2;
            }
#else
         case SDL_VIDEORESIZE:
            sdl->g_resized = true;
            sdl->g_new_width  = event.resize.w;
            sdl->g_new_height = event.resize.h;
#endif
            break;
         default:
            break;
      }
   }
