#ifndef _NO_LIBPNG
if ( strstrmatch(filename,".png")!=NULL )
	ret = GImageWritePng(image,filename,false);
    else
#endif
    if ( strstrmatch(filename,".bmp")!=NULL )
	ret = GImageWriteBmp(image,filename);
    else
	ff_post_error(_("Unsupported image format"),
#ifndef _NO_LIBPNG
		_("Unsupported image format must be bmp or png")
#else
		_("Unsupported image format must be bmp")
#endif
	    );
