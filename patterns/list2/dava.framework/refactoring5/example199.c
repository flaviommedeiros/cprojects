#ifndef LIBXML_REGEXP_ENABLED
if (repl != NULL)
		xmlSnprintfElements(&list[0], 5000, repl, 1);
	    else
#endif /* LIBXML_REGEXP_ENABLED */
		xmlSnprintfElements(&list[0], 5000, child, 1);
