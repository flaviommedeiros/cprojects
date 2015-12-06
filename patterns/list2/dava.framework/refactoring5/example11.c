#ifdef HAVE_SYS_MMAN_H
if (memory) {
		xmlChar *result;
		int len;

		if (encoding != NULL) {
		    if (format == 1) {
		        xmlDocDumpFormatMemoryEnc(doc, &result, &len, encoding, 1);
		    } else {
			xmlDocDumpMemoryEnc(doc, &result, &len, encoding);
		    }
		} else {
		    if (format == 1)
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
		    if (format == 1) {
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
		} else if (format == 1) {
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

                if (format == 1)
		    saveOpts |= XML_SAVE_FORMAT;
                else if (format == 2)
                    saveOpts |= XML_SAVE_WSNONSIG;

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
