#ifdef KSHVI
if (el->el_map.type == MAP_VI)
		el->el_line.cursor = el->el_line.buffer;
	else
#endif /* KSHVI */
		el->el_line.cursor = el->el_line.lastchar;
