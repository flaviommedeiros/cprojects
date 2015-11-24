#ifndef _NO_LIBPNG
if ( format==2 )
	    ret = GImageWritePng(&gi,filename,false);
	else
#endif
	    ret = GImageWriteBmp(&gi,filename);
