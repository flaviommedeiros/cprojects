#ifdef HAVE_SYS_MMAN_H
if (memory) {
		    int fd;
		    struct stat info;
		    const char *base;
		    if (stat(argv[i], &info) < 0) 
			break;
		    if ((fd = open(argv[i], O_RDONLY)) < 0)
			break;
		    base = mmap(NULL, info.st_size, PROT_READ,
			        MAP_SHARED, fd, 0) ;
		    if (base == (void *) MAP_FAILED)
			break;

		    ctxt = xmlSchemaNewMemParserCtxt((char *)base,info.st_size);

		    xmlSchemaSetParserErrors(ctxt,
			    (xmlSchemaValidityErrorFunc) fprintf,
			    (xmlSchemaValidityWarningFunc) fprintf,
			    stderr);
		    schema = xmlSchemaParse(ctxt);
		    xmlSchemaFreeParserCtxt(ctxt);
		    munmap((char *) base, info.st_size);
		} else
#endif
		{
		    ctxt = xmlSchemaNewParserCtxt(argv[i]);
		    xmlSchemaSetParserErrors(ctxt,
			    (xmlSchemaValidityErrorFunc) fprintf,
			    (xmlSchemaValidityWarningFunc) fprintf,
			    stderr);
		    schema = xmlSchemaParse(ctxt);
		    xmlSchemaFreeParserCtxt(ctxt);
		}
