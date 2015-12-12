#ifdef CONFIG_MODULES
if (THIS_MODULE != NULL)
			sprintf(buildtag, "srcversion: %-24s", THIS_MODULE->srcversion);
		else
#endif
			buildtag[0] = 'b';
