#ifdef GL_ES_VERSION_2_0
if( glConfig.ext.texture_non_power_of_two || ( ( flags & IT_GL_ES_NPOT ) == IT_GL_ES_NPOT ) )
#else
	if( glConfig.ext.texture_non_power_of_two )
#endif
	{
		width_ = min( viewportWidth, limit );
		height_ = min( viewportHeight, limit );
	}
	else
	{
		int d;

		// calculate the upper bound and make sure it's not a pow of 2
		d = min( limit, viewportWidth );
		if( ( d & (d-1) ) == 0 ) d--;
		for( width_ = 2; width_ <= d; width_ <<= 1 );

		d = min( limit, viewportHeight );
		if( ( d & (d-1) ) == 0 ) d--;
		for( height_ = 2; height_ <= d; height_ <<= 1 );

		if( size ) {
			while( width_ > size || height_ > size ) {
				width_ >>= 1;
				height_ >>= 1;
			}
		}
	}
