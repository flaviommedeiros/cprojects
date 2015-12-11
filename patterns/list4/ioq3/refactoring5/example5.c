#ifdef sparc
if (strcmp(arg, "-Bstatic") == 0 || strcmp(arg, "-Bdynamic") == 0)
			llist[1] = append(arg, llist[1]);
		else
#endif	
		{
		static char *path;
		if (path)
			error("-B overwrites earlier option", 0);
		path = arg + 2;
		if (strstr(com[1], "win32") != NULL)
			com[0] = concat(replace(path, '/', '\\'), concat("rcc", first(suffixes[4])));
		else
			com[0] = concat(path, "rcc");
		if (path[0] == 0)
			error("missing directory in -B option", 0);
		}
