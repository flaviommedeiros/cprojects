#ifdef HAVE_FBO
if (!gl->hw_render_fbo_init)
#endif
      {
         gl_update_input_size(gl, frame_width, frame_height, pitch, true);
         gl_copy_frame(gl, frame, frame_width, frame_height, pitch);
      }
