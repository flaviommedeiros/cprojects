#ifndef CIRCULAR_AREA
if( src->type == BL_PC ) { // Range for players' attacks and skills should always have a circular check. [Angezerus]
		if ( !check_distance_client_bl(src, bl, range) )
			return false;
	} else
#endif
	if( !check_distance_bl(src, bl, range) )
		return false;
