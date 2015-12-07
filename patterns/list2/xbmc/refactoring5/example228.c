#ifdef MULTIBYTE_CHAR
if(kflg)
	{
	    kflg = 0;
	}
	else if(iskanji(c))
	{
	    kflg = 1;
	}
	else
#endif
	    if(c == '\\' || c == DELIM || c == DELIM2)
	    {
		*p = delim;
		path = p + 1;
	    }
