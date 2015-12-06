if ( SCWorthOutputting(sc) && sc->ttf_glyph==-1
#if HANYANG
		&& (!iscff || !sc->compositionunit)
#endif
	) {
	    sc->ttf_glyph = j;
	    bygid[j++] = i;
	}
