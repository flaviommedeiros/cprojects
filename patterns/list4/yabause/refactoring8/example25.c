static const char fblit_img[] =
#if defined (_OGLES3_)
      "#version 300 es \n"
#else
      "#version 330 \n"
#endif
"precision mediump float;     \n"
"uniform sampler2D u_Src; \n"
"in vec2  v_Uv;          \n"
"out vec4 fragColor;            \n"
"void main () \n"
"{ \n"
"  vec4 src = texture2D( u_Src, v_Uv ); \n"
"  fragColor = src; \n"
"}\n";
