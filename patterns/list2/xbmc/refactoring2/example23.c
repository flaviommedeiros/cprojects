#ifndef SF_CLOSE_EACH_FILE
if(!IS_URL_SEEK_SAFE(rec->tf->url))
#endif
	{
	    close_file(rec->tf);
	    rec->tf = NULL;
	}
