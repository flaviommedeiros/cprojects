if ((window->flags & SDL_WINDOW_OPENGL) && 
        _this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES
#if SDL_VIDEO_OPENGL_GLX            
        && ( !_this->gl_data || ! _this->gl_data->HAS_GLX_EXT_create_context_es2_profile )
#endif  
    ) {
#if SDL_VIDEO_OPENGL_EGL  
        if (!_this->egl_data) {
            X11_XDestroyWindow(display, w);
            return -1;
        }

        /* Create the GLES window surface */
        windowdata->egl_surface = SDL_EGL_CreateSurface(_this, (NativeWindowType) w);

        if (windowdata->egl_surface == EGL_NO_SURFACE) {
            X11_XDestroyWindow(display, w);
            return SDL_SetError("Could not create GLES window surface");
        }
#else
        return SDL_SetError("Could not create GLES window surface (no EGL support available)");
#endif /* SDL_VIDEO_OPENGL_EGL */
    }
