const GLchar Yglprg_normal_f[] =
#if defined(_OGLES3_)
      "#version 300 es \n"
#else
      "#version 330 \n"
#endif
      "precision highp float;                            \n"
      "in highp vec4 v_texcoord;                            \n"
      "uniform vec4 u_color_offset;    \n"
      "uniform sampler2D s_texture;                        \n"
      "out vec4 fragColor;            \n"
      "void main()                                         \n"
      "{                                                   \n"
      "  ivec2 addr; \n"
      "  addr.x = int(v_texcoord.x);                        \n"
      "  addr.y = int(v_texcoord.y);                        \n"
      "  vec4 txcol = texelFetch( s_texture, addr,0 );         \n"
      "  if(txcol.a > 0.0)\n                                 "
      "     fragColor = clamp(txcol+u_color_offset,vec4(0.0),vec4(1.0));\n                         "
      "  else \n                                            "
      "     discard;\n                                      "
      "}                                                   \n";
