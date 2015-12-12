static const char vblit_img[] =
#if defined (_OGLES3_)
      "#version 300 es \n"
#else
      "#version 330 \n"
#endif
"layout (location = 0) in vec2 a_Position; \n"
"layout (location = 1) in vec2 a_Uv;       \n"
"uniform float u_w; \n"
"uniform float u_h; \n"
"out vec2	v_Uv;                    \n"  
"void main()                              \n"
"{                                        \n"
"   gl_Position = vec4((a_Position.x*u_w)-1.0, (a_Position.y*u_h)-1.0, 0.0, 1.0);  \n" 
"   v_Uv = a_Uv;                          \n"
"}";
