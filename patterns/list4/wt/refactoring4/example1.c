#if defined(_WIN32)
if (GL_TRUE == glewCreateContext(&visual))
#elif defined(__APPLE__) && !defined(GLEW_APPLE_GLX)
  if (GL_TRUE == glewCreateContext())
#else
  if (GL_TRUE == glewCreateContext(display, &visual))
#endif
  {
    fprintf(stderr, "Error: glewCreateContext failed\n");
    glewDestroyContext();
    return 1;
  }
