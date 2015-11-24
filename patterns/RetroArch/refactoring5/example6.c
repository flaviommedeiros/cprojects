#ifdef HAVE_OPENGL
if (use_gl)
      {
         float mix_factor = (min_pts - frames[0].pts) / (frames[1].pts - frames[0].pts);

         if (!temporal_interpolation)
            mix_factor = 1.0f;
         
         glBindFramebuffer(GL_FRAMEBUFFER, hw_render.get_current_framebuffer());
         glClearColor(0, 0, 0, 1);
         glClear(GL_COLOR_BUFFER_BIT);
         glViewport(0, 0, media.width, media.height);
         glUseProgram(prog);
         
         glUniform1f(mix_loc, mix_factor);
         glActiveTexture(GL_TEXTURE1);
         glBindTexture(GL_TEXTURE_2D, frames[1].tex);
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, frames[0].tex);
         
         
         glBindBuffer(GL_ARRAY_BUFFER, vbo);
         glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE,
               4 * sizeof(GLfloat), (const GLvoid*)(0 * sizeof(GLfloat)));
         glVertexAttribPointer(tex_loc, 2, GL_FLOAT, GL_FALSE,
               4 * sizeof(GLfloat), (const GLvoid*)(2 * sizeof(GLfloat)));
         glEnableVertexAttribArray(vertex_loc);
         glEnableVertexAttribArray(tex_loc);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
         glDisableVertexAttribArray(vertex_loc);
         glDisableVertexAttribArray(tex_loc);
         
         glUseProgram(0);
         glActiveTexture(GL_TEXTURE1);
         glBindTexture(GL_TEXTURE_2D, 0);
         glActiveTexture(GL_TEXTURE0);
         glBindTexture(GL_TEXTURE_2D, 0);
         
         CORE_PREFIX(video_cb)(RETRO_HW_FRAME_BUFFER_VALID, media.width, media.height, media.width * sizeof(uint32_t));
      }
      else
#endif
      {
         CORE_PREFIX(video_cb)(dupe ? NULL : video_frame_temp_buffer, media.width, media.height, media.width * sizeof(uint32_t));
      }
