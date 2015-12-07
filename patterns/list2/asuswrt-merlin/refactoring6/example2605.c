if(strncmp(url, APPLYAPPSTR, strlen(APPLYAPPSTR))==0 
#ifdef RTCONFIG_ROG
		|| strncmp(url, APPLYROGSTR, strlen(APPLYROGSTR))==0
#endif
	)
		fromapp=1;
	else if(strncmp(url, GETAPPSTR, strlen(GETAPPSTR))==0)  {
		fromapp=1;
		strcpy(url, url+strlen(GETAPPSTR));
		file += strlen(GETAPPSTR);
	}
