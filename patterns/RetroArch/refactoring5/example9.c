#ifdef HAVE_FBO
if (gl->fbo_inited)
      {
         gl_check_fbo_dimensions(gl);

         /* Go back to what we're supposed to do, 
          * render to FBO #0. */
         gl_start_frame_fbo(gl);
      }
      else
#endif
         gl_set_viewport(gl, width, height, false, true);
