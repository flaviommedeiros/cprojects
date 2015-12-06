#ifdef LIBXML_TREE_ENABLED
if ((!strcmp(argv[i], "-copy")) || (!strcmp(argv[i], "--copy")))
	    copy++;
	else
#endif /* LIBXML_TREE_ENABLED */
	if ((!strcmp(argv[i], "-recover")) ||
	         (!strcmp(argv[i], "--recover"))) {
	    recovery++;
	    options |= XML_PARSE_RECOVER;
	} else if ((!strcmp(argv[i], "-huge")) ||
	         (!strcmp(argv[i], "--huge"))) {
	    options |= XML_PARSE_HUGE;
	} else if ((!strcmp(argv[i], "-noent")) ||
	         (!strcmp(argv[i], "--noent"))) {
	    noent++;
	    options |= XML_PARSE_NOENT;
	} else if ((!strcmp(argv[i], "-nsclean")) ||
	         (!strcmp(argv[i], "--nsclean"))) {
	    options |= XML_PARSE_NSCLEAN;
	} else if ((!strcmp(argv[i], "-nocdata")) ||
	         (!strcmp(argv[i], "--nocdata"))) {
	    options |= XML_PARSE_NOCDATA;
	} else if ((!strcmp(argv[i], "-nodict")) ||
	         (!strcmp(argv[i], "--nodict"))) {
	    options |= XML_PARSE_NODICT;
	} else if ((!strcmp(argv[i], "-version")) ||
	         (!strcmp(argv[i], "--version"))) {
	    showVersion(argv[0]);
	    version = 1;
	} else if ((!strcmp(argv[i], "-noout")) ||
	         (!strcmp(argv[i], "--noout")))
	    noout++;
#ifdef LIBXML_OUTPUT_ENABLED
	else if ((!strcmp(argv[i], "-o")) ||
	         (!strcmp(argv[i], "-output")) ||
	         (!strcmp(argv[i], "--output"))) {
	    i++;
	    output = argv[i];
	}
#endif /* LIBXML_OUTPUT_ENABLED */
	else if ((!strcmp(argv[i], "-htmlout")) ||
	         (!strcmp(argv[i], "--htmlout")))
	    htmlout++;
	else if ((!strcmp(argv[i], "-nowrap")) ||
	         (!strcmp(argv[i], "--nowrap")))
	    nowrap++;
#ifdef LIBXML_HTML_ENABLED
	else if ((!strcmp(argv[i], "-html")) ||
	         (!strcmp(argv[i], "--html"))) {
	    html++;
        }
	else if ((!strcmp(argv[i], "-xmlout")) ||
	         (!strcmp(argv[i], "--xmlout"))) {
	    xmlout++;
	} else if ((!strcmp(argv[i], "-nodefdtd")) ||
	         (!strcmp(argv[i], "--nodefdtd"))) {
            nodefdtd++;
	    options |= HTML_PARSE_NODEFDTD;
        }
#endif /* LIBXML_HTML_ENABLED */
	else if ((!strcmp(argv[i], "-loaddtd")) ||
	         (!strcmp(argv[i], "--loaddtd"))) {
	    loaddtd++;
	    options |= XML_PARSE_DTDLOAD;
	} else if ((!strcmp(argv[i], "-dtdattr")) ||
	         (!strcmp(argv[i], "--dtdattr"))) {
	    loaddtd++;
	    dtdattrs++;
	    options |= XML_PARSE_DTDATTR;
	}
#ifdef LIBXML_VALID_ENABLED
	else if ((!strcmp(argv[i], "-valid")) ||
	         (!strcmp(argv[i], "--valid"))) {
	    valid++;
	    options |= XML_PARSE_DTDVALID;
	} else if ((!strcmp(argv[i], "-postvalid")) ||
	         (!strcmp(argv[i], "--postvalid"))) {
	    postvalid++;
	    loaddtd++;
	    options |= XML_PARSE_DTDLOAD;
	} else if ((!strcmp(argv[i], "-dtdvalid")) ||
	         (!strcmp(argv[i], "--dtdvalid"))) {
	    i++;
	    dtdvalid = argv[i];
	    loaddtd++;
	    options |= XML_PARSE_DTDLOAD;
	} else if ((!strcmp(argv[i], "-dtdvalidfpi")) ||
	         (!strcmp(argv[i], "--dtdvalidfpi"))) {
	    i++;
	    dtdvalidfpi = argv[i];
	    loaddtd++;
	    options |= XML_PARSE_DTDLOAD;
        }
#endif /* LIBXML_VALID_ENABLED */
	else if ((!strcmp(argv[i], "-dropdtd")) ||
	         (!strcmp(argv[i], "--dropdtd")))
	    dropdtd++;
	else if ((!strcmp(argv[i], "-insert")) ||
	         (!strcmp(argv[i], "--insert")))
	    insert++;
	else if ((!strcmp(argv[i], "-timing")) ||
	         (!strcmp(argv[i], "--timing")))
	    timing++;
	else if ((!strcmp(argv[i], "-auto")) ||
	         (!strcmp(argv[i], "--auto")))
	    generate++;
	else if ((!strcmp(argv[i], "-repeat")) ||
	         (!strcmp(argv[i], "--repeat"))) {
	    if (repeat)
	        repeat *= 10;
	    else
	        repeat = 100;
	}
#ifdef LIBXML_PUSH_ENABLED
	else if ((!strcmp(argv[i], "-push")) ||
	         (!strcmp(argv[i], "--push")))
	    push++;
#endif /* LIBXML_PUSH_ENABLED */
#ifdef HAVE_SYS_MMAN_H
	else if ((!strcmp(argv[i], "-memory")) ||
	         (!strcmp(argv[i], "--memory")))
	    memory++;
#endif
	else if ((!strcmp(argv[i], "-testIO")) ||
	         (!strcmp(argv[i], "--testIO")))
	    testIO++;
#ifdef LIBXML_XINCLUDE_ENABLED
	else if ((!strcmp(argv[i], "-xinclude")) ||
	         (!strcmp(argv[i], "--xinclude"))) {
	    xinclude++;
	    options |= XML_PARSE_XINCLUDE;
	}
	else if ((!strcmp(argv[i], "-noxincludenode")) ||
	         (!strcmp(argv[i], "--noxincludenode"))) {
	    xinclude++;
	    options |= XML_PARSE_XINCLUDE;
	    options |= XML_PARSE_NOXINCNODE;
	}
	else if ((!strcmp(argv[i], "-nofixup-base-uris")) ||
	         (!strcmp(argv[i], "--nofixup-base-uris"))) {
	    xinclude++;
	    options |= XML_PARSE_XINCLUDE;
	    options |= XML_PARSE_NOBASEFIX;
	}
#endif
#ifdef LIBXML_OUTPUT_ENABLED
#ifdef HAVE_ZLIB_H
	else if ((!strcmp(argv[i], "-compress")) ||
	         (!strcmp(argv[i], "--compress"))) {
	    compress++;
	    xmlSetCompressMode(9);
        }
#endif
#endif /* LIBXML_OUTPUT_ENABLED */
	else if ((!strcmp(argv[i], "-nowarning")) ||
	         (!strcmp(argv[i], "--nowarning"))) {
	    xmlGetWarningsDefaultValue = 0;
	    xmlPedanticParserDefault(0);
	    options |= XML_PARSE_NOWARNING;
        }
	else if ((!strcmp(argv[i], "-pedantic")) ||
	         (!strcmp(argv[i], "--pedantic"))) {
	    xmlGetWarningsDefaultValue = 1;
	    xmlPedanticParserDefault(1);
	    options |= XML_PARSE_PEDANTIC;
        }
#ifdef LIBXML_DEBUG_ENABLED
	else if ((!strcmp(argv[i], "-debugent")) ||
		 (!strcmp(argv[i], "--debugent"))) {
	    debugent++;
	    xmlParserDebugEntities = 1;
	}
#endif
#ifdef LIBXML_C14N_ENABLED
	else if ((!strcmp(argv[i], "-c14n")) ||
		 (!strcmp(argv[i], "--c14n"))) {
	    canonical++;
	    options |= XML_PARSE_NOENT | XML_PARSE_DTDATTR | XML_PARSE_DTDLOAD;
	}
	else if ((!strcmp(argv[i], "-c14n11")) ||
		 (!strcmp(argv[i], "--c14n11"))) {
	    canonical_11++;
	    options |= XML_PARSE_NOENT | XML_PARSE_DTDATTR | XML_PARSE_DTDLOAD;
	}
	else if ((!strcmp(argv[i], "-exc-c14n")) ||
		 (!strcmp(argv[i], "--exc-c14n"))) {
	    exc_canonical++;
	    options |= XML_PARSE_NOENT | XML_PARSE_DTDATTR | XML_PARSE_DTDLOAD;
	}
#endif
#ifdef LIBXML_CATALOG_ENABLED
	else if ((!strcmp(argv[i], "-catalogs")) ||
		 (!strcmp(argv[i], "--catalogs"))) {
	    catalogs++;
	} else if ((!strcmp(argv[i], "-nocatalogs")) ||
		 (!strcmp(argv[i], "--nocatalogs"))) {
	    nocatalogs++;
	}
#endif
	else if ((!strcmp(argv[i], "-encode")) ||
	         (!strcmp(argv[i], "--encode"))) {
	    i++;
	    encoding = argv[i];
	    /*
	     * OK it's for testing purposes
	     */
	    xmlAddEncodingAlias("UTF-8", "DVEnc");
        }
	else if ((!strcmp(argv[i], "-noblanks")) ||
	         (!strcmp(argv[i], "--noblanks"))) {
	     noblanks++;
	     xmlKeepBlanksDefault(0);
        }
	else if ((!strcmp(argv[i], "-maxmem")) ||
	         (!strcmp(argv[i], "--maxmem"))) {
	     i++;
	     if (sscanf(argv[i], "%d", &maxmem) == 1) {
	         xmlMemSetup(myFreeFunc, myMallocFunc, myReallocFunc,
		             myStrdupFunc);
	     } else {
	         maxmem = 0;
	     }
        }
	else if ((!strcmp(argv[i], "-format")) ||
	         (!strcmp(argv[i], "--format"))) {
	     noblanks++;
#ifdef LIBXML_OUTPUT_ENABLED
	     format = 1;
#endif /* LIBXML_OUTPUT_ENABLED */
	     xmlKeepBlanksDefault(0);
	}
	else if ((!strcmp(argv[i], "-pretty")) ||
	         (!strcmp(argv[i], "--pretty"))) {
	     i++;
#ifdef LIBXML_OUTPUT_ENABLED
	     format = atoi(argv[i]);
#endif /* LIBXML_OUTPUT_ENABLED */
	     if (format == 1) {
	         noblanks++;
	         xmlKeepBlanksDefault(0);
	     }
	}
#ifdef LIBXML_READER_ENABLED
	else if ((!strcmp(argv[i], "-stream")) ||
	         (!strcmp(argv[i], "--stream"))) {
	     stream++;
	}
	else if ((!strcmp(argv[i], "-walker")) ||
	         (!strcmp(argv[i], "--walker"))) {
	     walker++;
             noout++;
	}
#endif /* LIBXML_READER_ENABLED */
#ifdef LIBXML_SAX1_ENABLED
	else if ((!strcmp(argv[i], "-sax1")) ||
	         (!strcmp(argv[i], "--sax1"))) {
	    sax1++;
	    options |= XML_PARSE_SAX1;
	}
#endif /* LIBXML_SAX1_ENABLED */
	else if ((!strcmp(argv[i], "-sax")) ||
	         (!strcmp(argv[i], "--sax"))) {
	    sax++;
	}
	else if ((!strcmp(argv[i], "-chkregister")) ||
	         (!strcmp(argv[i], "--chkregister"))) {
	    chkregister++;
#ifdef LIBXML_SCHEMAS_ENABLED
	} else if ((!strcmp(argv[i], "-relaxng")) ||
	         (!strcmp(argv[i], "--relaxng"))) {
	    i++;
	    relaxng = argv[i];
	    noent++;
	    options |= XML_PARSE_NOENT;
	} else if ((!strcmp(argv[i], "-schema")) ||
	         (!strcmp(argv[i], "--schema"))) {
	    i++;
	    schema = argv[i];
	    noent++;
#endif
#ifdef LIBXML_SCHEMATRON_ENABLED
	} else if ((!strcmp(argv[i], "-schematron")) ||
	         (!strcmp(argv[i], "--schematron"))) {
	    i++;
	    schematron = argv[i];
	    noent++;
#endif
        } else if ((!strcmp(argv[i], "-nonet")) ||
                   (!strcmp(argv[i], "--nonet"))) {
	    options |= XML_PARSE_NONET;
	    xmlSetExternalEntityLoader(xmlNoNetExternalEntityLoader);
        } else if ((!strcmp(argv[i], "-nocompact")) ||
                   (!strcmp(argv[i], "--nocompact"))) {
	    options &= ~XML_PARSE_COMPACT;
	} else if ((!strcmp(argv[i], "-load-trace")) ||
	           (!strcmp(argv[i], "--load-trace"))) {
	    load_trace++;
        } else if ((!strcmp(argv[i], "-path")) ||
                   (!strcmp(argv[i], "--path"))) {
	    i++;
	    parsePath(BAD_CAST argv[i]);
#ifdef LIBXML_PATTERN_ENABLED
        } else if ((!strcmp(argv[i], "-pattern")) ||
                   (!strcmp(argv[i], "--pattern"))) {
	    i++;
	    pattern = argv[i];
#endif
#ifdef LIBXML_XPATH_ENABLED
        } else if ((!strcmp(argv[i], "-xpath")) ||
                   (!strcmp(argv[i], "--xpath"))) {
	    i++;
	    noout++;
	    xpathquery = argv[i];
#endif
	} else if ((!strcmp(argv[i], "-oldxml10")) ||
	           (!strcmp(argv[i], "--oldxml10"))) {
	    oldxml10++;
	    options |= XML_PARSE_OLD10;
	} else {
	    fprintf(stderr, "Unknown option %s\n", argv[i]);
	    usage(argv[0]);
	    return(1);
	}
