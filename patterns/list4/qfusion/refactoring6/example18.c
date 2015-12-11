if ((window->flags & SDL_WINDOW_OPENGL) &&
        _this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES
#if SDL_VIDEO_OPENGL_WGL           
        && (!_this->gl_data || !_this->gl_data->HAS_WGL_EXT_create_context_es2_profile)
#endif  
        ) {
#if SDL_VIDEO_OPENGL_EGL  
        if (WIN_GLES_SetupWindow(_this, window) < 0) {
            WIN_DestroyWindow(_this, window);
            return -1;
        }
#else
        return SDL_SetError("Could not create GLES window surface (no EGL support available)");
#endif /* SDL_VIDEO_OPENGL_EGL */
    } else 
#endif /* SDL_VIDEO_OPENGL_ES2 */

#if SDL_VIDEO_OPENGL_WGL
    if (window->flags & SDL_WINDOW_OPENGL) {
        if (WIN_GL_SetupWindow(_this, window) < 0) {
            WIN_DestroyWindow(_this, window);
            return -1;
        }
    }
