#ifdef INFINITIES
if( x == 0.0 )
#else
if( fabs(x) <= (fabs(y) / MAXNUM) )
#endif
	{
	if( code & 1 )
		{
#if ANSIC
		return( -PIO2 );
#else
		return( 3.0*PIO2 );
#endif
		}
	if( y == 0.0 )
		return( 0.0 );
	return( PIO2 );
	}
