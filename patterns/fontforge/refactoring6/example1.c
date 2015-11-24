if ( has_hints 
#ifndef _NO_PYTHON
         || (python_persistent!=NULL && PyMapping_Check((PyObject *)python_persistent))
#endif
       ) {

        xmlAddChild(retval, dictnode);
        /* Not officially part of the UFO/glif spec, but used by robofab */
	if ( has_hints ) {
            // Remember that the value of the plist key is in the node that follows it in the dict (not an x.m.l. child).
            xmlNewChild(dictnode, NULL, BAD_CAST "key", BAD_CAST "com.fontlab.hintData"); // Label the hint data block.
	    //                                           "    <key>com.fontlab.hintData</key>\n"
	    //                                           "    <dict>"
            xmlNodePtr hintdict = xmlNewChild(dictnode, NULL, BAD_CAST "dict", NULL);
            if ( sc != NULL ) {
	        if ( sc->hstem!=NULL ) {
                    StemInfo *h;
                    xmlNewChild(hintdict, NULL, BAD_CAST "key", BAD_CAST "hhints");
                    //                                   "      <key>hhints</key>"
                    //                                   "      <array>"
                    xmlNodePtr hintarray = xmlNewChild(hintdict, NULL, BAD_CAST "array", NULL);
                    for ( h = sc->hstem; h!=NULL; h=h->next ) {
                        char * valtmp = NULL;
                        xmlNodePtr stemdict = xmlNewChild(hintarray, NULL, BAD_CAST "dict", NULL);
		        //                               "        <dict>"
                        xmlNewChild(stemdict, NULL, BAD_CAST "key", "position");
		        //                               "          <key>position</key>"
                        xmlNewChildInteger(stemdict, NULL, BAD_CAST "integer", (int) rint(h->start));
		        //                               "          <integer>%d</integer>\n" ((int) rint(h->start))
                        xmlNewChild(stemdict, NULL, BAD_CAST "key", "width");
		        //                               "          <key>width</key>"
                        xmlNewChildInteger(stemdict, NULL, BAD_CAST "integer", (int) rint(h->width));
		        //                               "          <integer>%d</integer>\n" ((int) rint(h->width))
		        //                               "        </dict>\n"
		    }
		    //                                   "      </array>\n"
	        }
	        if ( sc->vstem!=NULL ) {
                    StemInfo *h;
                    xmlNewChild(hintdict, NULL, BAD_CAST "key", BAD_CAST "vhints");
                    //                                   "      <key>vhints</key>"
                    //                                   "      <array>"
                    xmlNodePtr hintarray = xmlNewChild(hintdict, NULL, BAD_CAST "array", NULL);
                    for ( h = sc->vstem; h!=NULL; h=h->next ) {
                        char * valtmp = NULL;
                        xmlNodePtr stemdict = xmlNewChild(hintarray, NULL, BAD_CAST "dict", NULL);
                        //                               "        <dict>"
                        xmlNewChild(stemdict, NULL, BAD_CAST "key", "position");
                        //                               "          <key>position</key>"
                        xmlNewChildInteger(stemdict, NULL, BAD_CAST "integer", (int) rint(h->start));
                        //                               "          <integer>%d</integer>\n" ((int) rint(h->start))
                        xmlNewChild(stemdict, NULL, BAD_CAST "key", "width");
                        //                               "          <key>width</key>"
                        xmlNewChildInteger(stemdict, NULL, BAD_CAST "integer", (int) rint(h->width));
                        //                               "          <integer>%d</integer>\n" ((int) rint(h->width))
                        //                               "        </dict>\n"
                    }
                    //                                   "      </array>\n"
	        }
	    }
	    //                                           "    </dict>"
	}
#ifndef _NO_PYTHON
        PyObject *dict = python_persistent, *items, *key, *value;
	/* Ok, look at the persistent data and output it (all except for a */
	/*  hint entry -- we've already handled that with the real hints, */
	/*  no point in retaining out of date hints too */
	if ( dict != NULL ) {
          if (!PyMapping_Check((PyObject *)python_persistent)) fprintf(stderr, "python_persistent is not a mapping.\n");
          else {
            int i, len;
            char *str;
	    items = PyMapping_Items(dict);
	    len = PySequence_Size(items);
	    for ( i=0; i<len; ++i ) {
			// According to the Python reference manual,
			// PySequence_GetItem returns a reference that we must release,
			// but PyTuple_GetItem returns a borrowed reference.
			PyObject *item = PySequence_GetItem(items,i);
			key = PyTuple_GetItem(item,0);
			if ( !PyBytes_Check(key))		/* Keys need not be strings */
			{ Py_DECREF(item); item = NULL; continue; }
			str = PyBytes_AsString(key);
			if ( !str || (strcmp(str,"com.fontlab.hintData")==0 && sc!=NULL) )	/* Already done */
			{ Py_DECREF(item); item = NULL; continue; }
			value = PyTuple_GetItem(item,1);
			if ( !value || !PyObjDumpable(value, has_lists))
			{ Py_DECREF(item); item = NULL; continue; }
			// "<key>%s</key>" str
      xmlNewChild(dictnode, NULL, BAD_CAST "key", str);
      xmlNodePtr tmpNode = PyObjectToXML(value, has_lists);
      xmlAddChild(dictnode, tmpNode);
			// "<...>...</...>"
			Py_DECREF(item); item = NULL;
	    }
	  }
	}
#endif
    }
