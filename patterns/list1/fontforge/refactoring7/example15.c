return( sc!=NULL &&
	( SCDrawsSomething(sc) || sc->widthset || sc->anchor!=NULL ||
#if HANYANG
	    sc->compositionunit ||
#endif
	    sc->dependents!=NULL /*||
	    sc->width!=sc->parent->ascent+sc->parent->descent*/ ) );
