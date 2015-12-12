#ifndef NO_OPENVG
if (thread->bound_api == EGL_OPENVG_API)
                  type = OPENVG;
               else
#endif
                  if (version == 1)
                     type = OPENGL_ES_11;
                  else
                     type = OPENGL_ES_20;
