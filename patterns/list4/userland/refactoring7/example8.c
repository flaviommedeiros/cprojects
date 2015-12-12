return (const GLubyte *)"GL_OES_compressed_ETC1_RGB8_texture "
                                 "GL_OES_compressed_paletted_texture "
                                 "GL_OES_texture_npot "  /*TODO is npot right? I can't find it in glext.h */
                                 "GL_OES_EGL_image "
                                 "GL_OES_EGL_image_external "
                                 "GL_EXT_discard_framebuffer "
                                 "GL_OES_query_matrix "
                                 "GL_OES_framebuffer_object "
                                 "GL_OES_rgb8_rgba8 "
                                 "GL_OES_depth24 "
                                 "GL_OES_depth32 "
                                 "GL_OES_stencil8 "
                                 "GL_OES_draw_texture "
                                 "GL_OES_mapbuffer "
#if GL_EXT_texture_format_BGRA8888
                                 "GL_EXT_texture_format_BGRA8888 "
#endif
#if GL_APPLE_rgb_422
                                 "GL_APPLE_rgb_422 "
#endif
#if GL_OES_matrix_palette
                                 "GL_OES_matrix_palette "
#endif
#ifdef GL_EXT_debug_marker
                                 "GL_EXT_debug_marker "
#endif
                                 ;
