#ifndef _NO_LIBPNG
if ( strstrmatch(cret,".png")!=NULL )
	ret = GImageWritePng(image,cret,false);
    else
#endif
    if ( strstrmatch(cret,".bmp")!=NULL )
	ret = GImageWriteBmp(image,cret);
    else
	ff_post_error(_("Unsupported image format"),
#ifndef _NO_LIBPNG
		_("Unsupported image format must be bmp or png")
#else
		_("Unsupported image format must be bmp")
#endif
	    );
