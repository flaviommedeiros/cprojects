if ( pt==NULL || (strmatch(pt,".bmp")!=0
#ifndef _NO_LIBPNG
	    && strmatch(pt,".png")!=0
#endif
	    ))
	ScriptError( c, "Unsupported image format");
