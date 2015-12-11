#ifndef GL_ES_VERSION_2_0
if( glConfig.shadingLanguageVersion < 400 && glConfig.ext.draw_instanced )
		shaderStrings[i++] = QF_GLSL_ENABLE_ARB_DRAW_INSTANCED;
	else
#endif
		shaderStrings[i++] = "\n";
