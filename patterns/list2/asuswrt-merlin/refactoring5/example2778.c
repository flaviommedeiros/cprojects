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

		    ctxt = xmlRelaxNGNewMemParserCtxt((char *)base,info.st_size);

		    xmlRelaxNGSetParserErrors(ctxt,
			    (xmlRelaxNGValidityErrorFunc) fprintf,
			    (xmlRelaxNGValidityWarningFunc) fprintf,
			    stderr);
		    schema = xmlRelaxNGParse(ctxt);
		    xmlRelaxNGFreeParserCtxt(ctxt);
		    munmap((char *) base, info.st_size);
		} else
#endif
		{
		    ctxt = xmlRelaxNGNewParserCtxt(argv[i]);
		    xmlRelaxNGSetParserErrors(ctxt,
			    (xmlRelaxNGValidityErrorFunc) fprintf,
			    (xmlRelaxNGValidityWarningFunc) fprintf,
			    stderr);
		    schema = xmlRelaxNGParse(ctxt);
		    xmlRelaxNGFreeParserCtxt(ctxt);
		}
