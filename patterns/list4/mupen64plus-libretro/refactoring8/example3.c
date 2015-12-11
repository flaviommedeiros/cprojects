static const char* vertex_shader =
SHADER_HEADER
#if defined(__LIBRETRO__) && !defined(HAVE_OPENGLES2) // Desktop GL fix
"#define highp                         \n"
#endif
"#define Z_MAX 65536.0                 \n"
"attribute highp vec4 aPosition;         \n"
"attribute highp vec4 aColor;          \n"
"attribute highp vec4 aMultiTexCoord0; \n"
"attribute highp vec4 aMultiTexCoord1; \n"
"attribute float aFog;                 \n"
"uniform vec3 vertexOffset;            \n" //Moved some calculations from grDrawXXX to shader
"uniform vec4 textureSizes;            \n" 
"uniform vec3 fogModeEndScale;         \n" //0 = Mode, 1 = gl_Fog.end, 2 = gl_Fog.scale
SHADER_VARYING
"\n"
"void main()\n"
"{\n"
"  highp float q = aPosition.w;                                                     \n"
"  highp float invertY = vertexOffset.z;                                          \n" //Usually 1.0 but -1.0 when rendering to a texture (see inverted_culling grRenderBuffer)
"  gl_Position.x = (aPosition.x - vertexOffset.x) / vertexOffset.x;           \n"
"  gl_Position.y = invertY *-(aPosition.y - vertexOffset.y) / vertexOffset.y; \n"
"  gl_Position.z = aPosition.z / Z_MAX;                                       \n"
"  gl_Position.w = 1.0;                                                     \n"
"  gl_Position /= q;                                                        \n"
"  gl_FrontColor = aColor.bgra;                                             \n"
"\n"
"  gl_TexCoord[0] = vec4(aMultiTexCoord0.xy / q / textureSizes.xy,0,1);     \n"
"  gl_TexCoord[1] = vec4(aMultiTexCoord1.xy / q / textureSizes.zw,0,1);     \n"
"\n"
"  float fogV = (1.0 / mix(q,aFog,fogModeEndScale[0])) / 255.0;             \n"
//"  //if(fogMode == 2) {                                                     \n"
//"  //  fogV = 1.0 / aFog / 255                                              \n"
//"  //}                                                                      \n"
"\n"
"  float f = (fogModeEndScale[1] - fogV) * fogModeEndScale[2];              \n"
"  f = clamp(f, 0.0, 1.0);                                                  \n"
"  gl_TexCoord[0].b = f;                                                    \n"
"  gl_TexCoord[2].b = aPosition.x;                                            \n" 
"  gl_TexCoord[2].a = aPosition.y;                                            \n" 
"}                                                                          \n" 
;
