#ifdef GL_ES_VERSION_2_0
if( !glConfig.ext.texture_non_power_of_two && ( ( flags & IT_GL_ES_NPOT ) != IT_GL_ES_NPOT ) && !forceNPOT )
#else
	if( !glConfig.ext.texture_non_power_of_two && !forceNPOT )
#endif
	{
		int potWidth, potHeight;

		for( potWidth = 1; potWidth < width; potWidth <<= 1 );
		for( potHeight = 1; potHeight < height; potHeight <<= 1 );

		if( ( width != potWidth ) || ( height != potHeight ) )
			mips = 1;

		width = potWidth;
		height = potHeight;
	}
