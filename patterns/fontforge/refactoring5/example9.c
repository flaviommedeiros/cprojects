#ifndef _NO_LIBPNG
if ( strcmp(mimetype,"image/png")==0 )
	img = GImageRead_Png(tmp);
    else
#endif
#ifndef _NO_LIBJPEG
    if ( strcmp(mimetype,"image/jpeg")==0 )
	img = GImageRead_Jpeg(tmp);
    else
#endif
    if ( strcmp(mimetype,"image/bmp")==0 )
	img = GImageRead_Bmp(tmp);
    else
	img = NULL;
