#ifdef GL_ES_VERSION_2_0
if( glConfig.shadingLanguageVersion < 300 )
#endif
	{
#ifdef GL_ES_VERSION_2_0
		if( glConfig.ext.shadow )
			shaderStrings[enableShadowIdx] = QF_GLSL_ENABLE_EXT_SHADOW_SAMPLERS;
		if( glConfig.ext.texture3D )
			shaderStrings[enableTexture3DIdx] = QF_GLSL_ENABLE_OES_TEXTURE_3D;
#endif
		if( glConfig.ext.texture_array )
			shaderStrings[enableTextureArrayIdx] = QF_GLSL_ENABLE_EXT_TEXTURE_ARRAY;
	}
