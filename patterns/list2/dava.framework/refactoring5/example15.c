#ifdef LIBXML_READER_ENABLED
if (stream != 0)
		    streamFile(argv[i]);
		else
#endif /* LIBXML_READER_ENABLED */
                if (sax) {
		    testSAX(argv[i]);
		} else {
		    parseAndPrintFile(argv[i], NULL);
		}