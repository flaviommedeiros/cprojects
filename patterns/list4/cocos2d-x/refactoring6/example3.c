if (!strcmp(buf, "#if LJ_52\n"))
	  ok = LJ_52;
	else if (!strcmp(buf, "#if LJ_HASJIT\n"))
	  ok = LJ_HASJIT;
	else if (!strcmp(buf, "#if LJ_HASFFI\n"))
	  ok = LJ_HASFFI;
