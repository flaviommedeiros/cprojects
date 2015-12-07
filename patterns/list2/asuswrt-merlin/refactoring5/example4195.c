#ifdef LIBXML_VALID_ENABLED
if ((insert) && (!html)) {
        const xmlChar* list[256];
	int nb, i;
	xmlNodePtr node;

	if (doc->children != NULL) {
	    node = doc->children;
	    while ((node != NULL) && (node->last == NULL)) node = node->next;
	    if (node != NULL) {
		nb = xmlValidGetValidElements(node->last, NULL, list, 256);
		if (nb < 0) {
		    fprintf(stderr, "could not get valid list of elements\n");
		} else if (nb == 0) {
		    fprintf(stderr, "No element can be inserted under root\n");
		} else {
		    fprintf(stderr, "%d element types can be inserted under root:\n",
		           nb);
		    for (i = 0;i < nb;i++) {
			 fprintf(stderr, "%s\n", (char *) list[i]);
		    }
		}
	    }
	}
    }else
#endif /* LIBXML_VALID_ENABLED */
#ifdef LIBXML_READER_ENABLED
    if (walker) {
        walkDoc(doc);
    }
