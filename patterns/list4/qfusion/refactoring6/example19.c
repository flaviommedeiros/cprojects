if (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES 
#if SDL_VIDEO_OPENGL_GLX            
            && ( !_this->gl_data || ! _this->gl_data->HAS_GLX_EXT_create_context_es2_profile )
#endif
        ) {
            vinfo = X11_GLES_GetVisual(_this, display, screen);
        } else
#endif
        {
#if SDL_VIDEO_OPENGL_GLX
            vinfo = X11_GL_GetVisual(_this, display, screen);
#endif
        }
