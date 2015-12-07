#ifdef LIBXML_OUTPUT_ENABLED
if (noout == 0) {
        int ret;

	/*
	 * print it.
	 */
#ifdef LIBXML_DEBUG_ENABLED
	if (!debug) {
#endif
	    if ((timing) && (!repeat)) {
		startTimer();
	    }
#ifdef LIBXML_HTML_ENABLED
            if ((html) && (!xmlout)) {
		if (compress) {
		    htmlSaveFile(output ? output : "-", doc);
		}
		else if (encoding != NULL) {
		    if ( format ) {
			htmlSaveFileFormat(output ? output : "-", doc, encoding, 1);
		    }
		    else {
			htmlSaveFileFormat(output ? output : "-", doc, encoding, 0);
		    }
		}
		else if (format) {
		    htmlSaveFileFormat(output ? output : "-", doc, NULL, 1);
		}
		else {
		    FILE *out;
		    if (output == NULL)
			out = stdout;
		    else {
			out = fopen(output,"wb");
		    }
		    if (out != NULL) {
			if (htmlDocDump(out, doc) < 0)
			    progresult = XMLLINT_ERR_OUT;

			if (output != NULL)
			    fclose(out);
		    } else {
			fprintf(stderr, "failed to open %s\n", output);
			progresult = XMLLINT_ERR_OUT;
		    }
		}
		if ((timing) && (!repeat)) {
		    endTimer("Saving");
		}
	    } else
#endif
#ifdef LIBXML_C14N_ENABLED
            if (canonical) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_1_0, NULL, 1, &result);
		if (size >= 0) {
		    write(1, result, size);
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else if (canonical) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_1_1, NULL, 1, &result);
		if (size >= 0) {
		    write(1, result, size);
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else
            if (exc_canonical) {
	        xmlChar *result = NULL;
		int size;

		size = xmlC14NDocDumpMemory(doc, NULL, XML_C14N_EXCLUSIVE_1_0, NULL, 1, &result);
		if (size >= 0) {
		    write(1, result, size);
		    xmlFree(result);
		} else {
		    fprintf(stderr, "Failed to canonicalize\n");
		    progresult = XMLLINT_ERR_OUT;
		}
	    } else
#endif
#ifdef HAVE_SYS_MMAN_H
	    if (memory) {
		xmlChar *result;
		int len;

		if (encoding != NULL) {
		    if ( format ) {
		        xmlDocDumpFormatMemoryEnc(doc, &result, &len, encoding, 1);
		    } else {
			xmlDocDumpMemoryEnc(doc, &result, &len, encoding);
		    }
		} else {
		    if (format)
			xmlDocDumpFormatMemory(doc, &result, &len, 1);
		    else
			xmlDocDumpMemory(doc, &result, &len);
		}
		if (result == NULL) {
		    fprintf(stderr, "Failed to save\n");
		    progresult = XMLLINT_ERR_OUT;
		} else {
		    write(1, result, len);
		    xmlFree(result);
		}

	    } else
#endif /* HAVE_SYS_MMAN_H */
	    if (compress) {
		xmlSaveFile(output ? output : "-", doc);
	    } else if (oldout) {
	        if (encoding != NULL) {
		    if ( format ) {
			ret = xmlSaveFormatFileEnc(output ? output : "-", doc,
						   encoding, 1);
		    }
		    else {
			ret = xmlSaveFileEnc(output ? output : "-", doc,
			                     encoding);
		    }
		    if (ret < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		} else if (format) {
		    ret = xmlSaveFormatFile(output ? output : "-", doc, 1);
		    if (ret < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		} else {
		    FILE *out;
		    if (output == NULL)
			out = stdout;
		    else {
			out = fopen(output,"wb");
		    }
		    if (out != NULL) {
			if (xmlDocDump(out, doc) < 0)
			    progresult = XMLLINT_ERR_OUT;

			if (output != NULL)
			    fclose(out);
		    } else {
			fprintf(stderr, "failed to open %s\n", output);
			progresult = XMLLINT_ERR_OUT;
		    }
		}
	    } else {
	        xmlSaveCtxtPtr ctxt;
		int saveOpts = 0;

                if (format)
		    saveOpts |= XML_SAVE_FORMAT;

#if defined(LIBXML_HTML_ENABLED) || defined(LIBXML_VALID_ENABLED)
                if (xmlout)
                    saveOpts |= XML_SAVE_AS_XML;
#endif

		if (output == NULL)
		    ctxt = xmlSaveToFd(1, encoding, saveOpts);
		else
		    ctxt = xmlSaveToFilename(output, encoding, saveOpts);

		if (ctxt != NULL) {
		    if (xmlSaveDoc(ctxt, doc) < 0) {
			fprintf(stderr, "failed save to %s\n",
				output ? output : "-");
			progresult = XMLLINT_ERR_OUT;
		    }
		    xmlSaveClose(ctxt);
		} else {
		    progresult = XMLLINT_ERR_OUT;
		}
	    }
	    if ((timing) && (!repeat)) {
		endTimer("Saving");
	    }
#ifdef LIBXML_DEBUG_ENABLED
	} else {
	    FILE *out;
	    if (output == NULL)
	        out = stdout;
	    else {
		out = fopen(output,"wb");
	    }
	    if (out != NULL) {
		xmlDebugDumpDocument(out, doc);

		if (output != NULL)
		    fclose(out);
	    } else {
		fprintf(stderr, "failed to open %s\n", output);
		progresult = XMLLINT_ERR_OUT;
	    }
	}
#endif
    }
