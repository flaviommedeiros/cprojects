#if defined(_GLFW_X11)
if (window->context.api != GLFW_OPENGL_API)
#endif // _GLFW_X11
    {
        if (window->context.egl.client)
        {
            _glfw_dlclose(window->context.egl.client);
            window->context.egl.client = NULL;
        }
    }
