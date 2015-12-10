switch (b->method) {
    case RAW:
	return 0;

    case GZIP:
	uncomp = zlib_mem_inflate((char *)b->data, b->comp_size, &uncomp_size);
	if (!uncomp)
	    return -1;
	if ((int)uncomp_size != b->uncomp_size) {
	    free(uncomp);
	    return -1;
	}
	free(b->data);
	b->data = (unsigned char *)uncomp;
	b->alloc = uncomp_size;
	b->method = RAW;
	break;

#ifdef HAVE_LIBBZ2
    case BZIP2: {
	unsigned int usize = b->uncomp_size;
	if (!(uncomp = malloc(usize)))
	    return -1;
	if (BZ_OK != BZ2_bzBuffToBuffDecompress(uncomp, &usize,
						(char *)b->data, b->comp_size,
						0, 0)) {
	    free(uncomp);
	    return -1;
	}
	free(b->data);
	b->data = (unsigned char *)uncomp;
	b->alloc = usize;
	b->method = RAW;
	b->uncomp_size = usize; // Just incase it differs
	break;
    }
#else
    case BZIP2:
	fprintf(stderr, "Bzip2 compression is not compiled into this "
		"version.\nPlease rebuild and try again.\n");
	return -1;
#endif

#ifdef HAVE_LIBLZMA
    case LZMA:
	uncomp = lzma_mem_inflate((char *)b->data, b->comp_size, &uncomp_size);
	if (!uncomp)
	    return -1;
	if ((int)uncomp_size != b->uncomp_size)
	    return -1;
	free(b->data);
	b->data = (unsigned char *)uncomp;
	b->alloc = uncomp_size;
	b->method = RAW;
	break;
#else
    case LZMA:
	fprintf(stderr, "Lzma compression is not compiled into this "
		"version.\nPlease rebuild and try again.\n");
	return -1;
	break;
#endif

    case RANS: {
	unsigned int usize = b->uncomp_size, usize2;
	uncomp = (char *)rans_uncompress(b->data, b->comp_size, &usize2);
	if (!uncomp || usize != usize2)
 	    return -1;
	free(b->data);
	b->data = (unsigned char *)uncomp;
	b->alloc = usize2;
	b->method = RAW;
	b->uncomp_size = usize2; // Just incase it differs
	//fprintf(stderr, "Expanded %d to %d\n", b->comp_size, b->uncomp_size);
	break;
    }

    default:
	return -1;
    }
