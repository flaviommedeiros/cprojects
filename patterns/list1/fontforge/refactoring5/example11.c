#ifndef _NO_LIBPNG
if ( type==6 )
		image = GImageRead_Png(temp);
	    else
#endif
		image = GImageRead_Bmp(temp);
