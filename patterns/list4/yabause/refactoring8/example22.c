const GLchar Yglprg_vdp2_drawfb_addcolor_f[] =
#if defined(_OGLES3_)
"#version 300 es \n"
#else
"#version 330 \n"
#endif
"precision highp float;\n"
"in vec2 v_texcoord;\n"
"uniform sampler2D s_vdp1FrameBuffer;\n"
"uniform float u_from;\n"
"uniform float u_to;\n"
"uniform vec4 u_coloroffset;\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
"  vec2 addr = v_texcoord;\n"
"  highp vec4 fbColor = texture(s_vdp1FrameBuffer,addr);\n"
"  int additional = int(fbColor.a * 255.0);\n"
"  highp float alpha = float((additional/8)*8)/255.0;\n"
"  highp float depth = (float(additional&0x07)/10.0) + 0.05;\n"
"  if( depth < u_from || depth > u_to ){ discard;return;}\n"
"  if( alpha <= 0.0){\n"
"     discard;\n"
"  }else if( alpha >= 0.75){\n"
"     fragColor = fbColor;\n"
"     fragColor += u_coloroffset;  \n"
"     fragColor.a = 0.0;\n"
"     gl_FragDepth =  (depth+1.0)/2.0;\n"
"  }else{\n"
"     fragColor = fbColor;\n"
"     fragColor += u_coloroffset;\n"
"     fragColor.a = 1.0;\n"
"     gl_FragDepth =  (depth+1.0)/2.0;\n"
"  }\n " 
"}\n";