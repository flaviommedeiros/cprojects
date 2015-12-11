const char *_vert = "                                       \n"
#if defined(__LIBRETRO__) && !defined(HAVE_OPENGLES2) // Desktop GL fix
"#version 120                                               \n"
"#define highp                                              \n"
"#define lowp                                               \n"
"#define mediump                                            \n"
#endif
"attribute highp vec4 	aPosition;                          \n"\
"attribute lowp vec4 	aColor;                             \n"\
"attribute highp vec2   aTexCoord0;                         \n"\
"attribute highp vec2   aTexCoord1;                         \n"\
"                                                           \n"\
"uniform bool		    uEnableFog;                         \n"\
"uniform float			 uFogScale, uFogOffset;         \n"\
"uniform float 			uRenderState;                       \n"\
"                                                           \n"\
"uniform mediump vec2 	uTexScale;                          \n"\
"uniform mediump vec2 	uTexOffset[2];                      \n"\
"uniform mediump vec2 	uCacheShiftScale[2];                \n"\
"uniform mediump vec2 	uCacheScale[2];                     \n"\
"uniform mediump vec2 	uCacheOffset[2];                    \n"\
"                                                           \n"\
"varying lowp float     vFactor;                            \n"\
"varying lowp vec4 		vShadeColor;                        \n"\
"varying mediump vec2 	vTexCoord0;                         \n"\
"varying mediump vec2 	vTexCoord1;                         \n"\
"                                                           \n"\
"void main()                                                \n"\
"{                                                          \n"\
"gl_Position = aPosition;                                   \n"\
"vShadeColor = aColor;                                      \n"\
"                                                           \n"\
"if (uRenderState == 1.0)                                   \n"\
"{                                                          \n"\
"vTexCoord0 = (aTexCoord0 * (uTexScale[0] *                 \n"\
"           uCacheShiftScale[0]) + (uCacheOffset[0] -       \n"\
"           uTexOffset[0])) * uCacheScale[0];               \n"\
"vTexCoord1 = (aTexCoord0 * (uTexScale[1] *                 \n"\
"           uCacheShiftScale[1]) + (uCacheOffset[1] -       \n"\
"           uTexOffset[1])) * uCacheScale[1];               \n"\
"}                                                          \n"\
"else                                                       \n"\
"{                                                          \n"\
"vTexCoord0 = aTexCoord0;                                   \n"\
"vTexCoord1 = aTexCoord1;                                   \n"\
"}                                                          \n"\
"                                                           \n";
