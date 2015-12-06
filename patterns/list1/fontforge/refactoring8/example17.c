static void buildtablestructures(struct alltabs *at, SplineFont *sf,
	enum fontformat format) {
    int i;
    int ebdtpos, eblcpos;
    struct ttf_table *tab;

    if ( format==ff_otf || format==ff_otfcid ) {
	at->tabdir.version = CHR('O','T','T','O');
#ifdef FONTFORGE_CONFIG_APPLE_ONLY_TTF		/* This means that Windows will reject the font. In general not a good idea */
    } else if ( at->applemode && !at->opentypemode ) {
	at->tabdir.version = CHR('t','r','u','e');
#endif
    } else {
	at->tabdir.version = 0x00010000;
    }

    i = 0;

    if ( at->base!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('B','A','S','E');
	at->tabdir.tabs[i].data = at->base;
	at->tabdir.tabs[i++].length = at->baselen;
    }

    if ( at->bsln!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('b','s','l','n');
	at->tabdir.tabs[i].data = at->bsln;
	at->tabdir.tabs[i++].length = at->bslnlen;
    }

    if ( at->bdf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('B','D','F',' ');
	at->tabdir.tabs[i].data = at->bdf;
	at->tabdir.tabs[i++].length = at->bdflen;
    }

    if ( format==ff_otf || format==ff_otfcid ) {
	at->tabdir.tabs[i].tag = CHR('C','F','F',' ');
	at->tabdir.tabs[i].length = at->cfflen;
	at->tabdir.tabs[i++].data = at->cfff;
    }

    if ( at->dsigf!=NULL ) {
	ebdtpos = i;
	at->tabdir.tabs[i].tag = CHR('D','S','I','G');
	at->tabdir.tabs[i].length = at->dsiglen;
	at->tabdir.tabs[i++].data = at->dsigf;
    }

    if ( at->bdat!=NULL && (at->msbitmaps || at->otbbitmaps)) {
	ebdtpos = i;
	at->tabdir.tabs[i].tag = CHR('E','B','D','T');
	at->tabdir.tabs[i].length = at->bdatlen;
	at->tabdir.tabs[i++].data = at->bdat;
    }

    if ( at->bloc!=NULL && (at->msbitmaps || at->otbbitmaps)) {
	eblcpos = i;
	at->tabdir.tabs[i].tag = CHR('E','B','L','C');
	at->tabdir.tabs[i].data = at->bloc;
	at->tabdir.tabs[i++].length = at->bloclen;
    }

    if ( at->ebsc!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('E','B','S','C');
	at->tabdir.tabs[i].data = at->ebsc;
	at->tabdir.tabs[i++].length = at->ebsclen;
    }

    if ( at->fftmf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('F','F','T','M');
	at->tabdir.tabs[i].data = at->fftmf;
	at->tabdir.tabs[i++].length = at->fftmlen;
    }

    if ( at->gdef!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('G','D','E','F');
	at->tabdir.tabs[i].data = at->gdef;
	at->tabdir.tabs[i++].length = at->gdeflen;
    }

    if ( at->gpos!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('G','P','O','S');
	at->tabdir.tabs[i].data = at->gpos;
	at->tabdir.tabs[i++].length = at->gposlen;
    }

    if ( at->gsub!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('G','S','U','B');
	at->tabdir.tabs[i].data = at->gsub;
	at->tabdir.tabs[i++].length = at->gsublen;
    }

    if ( at->jstf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('J','S','T','F');
	at->tabdir.tabs[i].data = at->jstf;
	at->tabdir.tabs[i++].length = at->jstflen;
    }

    if ( at->os2f!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('O','S','/','2');
	at->tabdir.tabs[i].data = at->os2f;
	at->tabdir.tabs[i++].length = at->os2len;
    }

    if ( at->pfed!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('P','f','E','d');
	at->tabdir.tabs[i].data = at->pfed;
	at->tabdir.tabs[i++].length = at->pfedlen;
    }

    if ( at->tex!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('T','e','X',' ');
	at->tabdir.tabs[i].data = at->tex;
	at->tabdir.tabs[i++].length = at->texlen;
    }

    if ( at->math!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('M','A','T','H');
	at->tabdir.tabs[i].data = at->math;
	at->tabdir.tabs[i++].length = at->mathlen;
    }

    if ( at->vorgf!=NULL ) {		/* No longer generated */
	at->tabdir.tabs[i].tag = CHR('V','O','R','G');
	at->tabdir.tabs[i].data = at->vorgf;
	at->tabdir.tabs[i++].length = at->vorglen;
    }

    if ( at->acnt!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('a','c','n','t');
	at->tabdir.tabs[i].data = at->acnt;
	at->tabdir.tabs[i++].length = at->acntlen;
    }

    if ( at->bdat!=NULL && at->applebitmaps ) {
	at->tabdir.tabs[i].tag = CHR('b','d','a','t');
	if ( !at->msbitmaps ) {
	    at->tabdir.tabs[i].data = at->bdat;
	    at->tabdir.tabs[i++].length = at->bdatlen;
	} else {
	    at->tabdir.tabs[i].data = NULL;
	    at->tabdir.tabs[i].dup_of = ebdtpos;
	    at->tabdir.tabs[i++].length = at->tabdir.tabs[ebdtpos].length;
	}
    }

    if ( format==ff_none && at->applebitmaps ) {
	/* Bitmap only fonts get a bhed table rather than a head */
	at->tabdir.tabs[i].tag = CHR('b','h','e','d');
	at->tabdir.tabs[i].data = at->headf;
	at->tabdir.tabs[i++].length = at->headlen;
    }

    if ( at->bloc!=NULL && at->applebitmaps ) {
	at->tabdir.tabs[i].tag = CHR('b','l','o','c');
	if ( !at->msbitmaps ) {
	    at->tabdir.tabs[i].data = at->bloc;
	    at->tabdir.tabs[i++].length = at->bloclen;
	} else {
	    at->tabdir.tabs[i].data = NULL;
	    at->tabdir.tabs[i].dup_of = eblcpos;
	    at->tabdir.tabs[i++].length = at->tabdir.tabs[eblcpos].length;
	}
    }

    if ( at->cmap!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('c','m','a','p');
	at->tabdir.tabs[i].data = at->cmap;
	at->tabdir.tabs[i++].length = at->cmaplen;
    }

    if ( format!=ff_otf && format!=ff_otfcid && format!=ff_none ) {
	if ( at->cvtf!=NULL ) {
	    at->tabdir.tabs[i].tag = CHR('c','v','t',' ');
	    at->tabdir.tabs[i].data = at->cvtf;
	    at->tabdir.tabs[i++].length = at->cvtlen;
	}
    }

    if ( at->feat!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('f','e','a','t');
	at->tabdir.tabs[i].data = at->feat;
	at->tabdir.tabs[i++].length = at->featlen;
    }

    if ( at->fpgmf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('f','p','g','m');
	at->tabdir.tabs[i].data = at->fpgmf;
	at->tabdir.tabs[i++].length = at->fpgmlen;
    }

    if ( at->gaspf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('g','a','s','p');
	at->tabdir.tabs[i].data = at->gaspf;
	at->tabdir.tabs[i++].length = at->gasplen;
    }

    if ( at->gi.glyphs!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('g','l','y','f');
	at->tabdir.tabs[i].data = at->gi.glyphs;
	at->tabdir.tabs[i++].length = at->gi.glyph_len;
    }

    if ( at->hdmxf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('h','d','m','x');
	at->tabdir.tabs[i].data = at->hdmxf;
	at->tabdir.tabs[i++].length = at->hdmxlen;
    }

    if ( format!=ff_none || !at->applebitmaps ) {
	at->tabdir.tabs[i].tag = CHR('h','e','a','d');
	at->tabdir.tabs[i].data = at->headf;
	at->tabdir.tabs[i++].length = at->headlen;
    }

    if ( format!=ff_none || !at->applemode ) {
	at->tabdir.tabs[i].tag = CHR('h','h','e','a');
	at->tabdir.tabs[i].data = at->hheadf;
	at->tabdir.tabs[i++].length = at->hheadlen;
    } else if ( at->hheadf!=NULL ) {
	fclose(at->hheadf);
	at->hheadf = NULL;
    }

    if ( format!=ff_none || !at->applemode ) {
	at->tabdir.tabs[i].tag = CHR('h','m','t','x');
	at->tabdir.tabs[i].data = at->gi.hmtx;
	at->tabdir.tabs[i++].length = at->gi.hmtxlen;
    }

    if ( at->kern!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('k','e','r','n');
	at->tabdir.tabs[i].data = at->kern;
	at->tabdir.tabs[i++].length = at->kernlen;
    }

    if ( at->lcar!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('l','c','a','r');
	at->tabdir.tabs[i].data = at->lcar;
	at->tabdir.tabs[i++].length = at->lcarlen;
    }

    if ( at->loca!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('l','o','c','a');
	at->tabdir.tabs[i].data = at->loca;
	at->tabdir.tabs[i++].length = at->localen;
    }

    at->tabdir.tabs[i].tag = CHR('m','a','x','p');
    at->tabdir.tabs[i].data = at->maxpf;
    at->tabdir.tabs[i++].length = at->maxplen;

    if ( at->morx!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('m','o','r','x');
	at->tabdir.tabs[i].data = at->morx;
	at->tabdir.tabs[i++].length = at->morxlen;
    }

    if ( at->name!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('n','a','m','e');
	at->tabdir.tabs[i].data = at->name;
	at->tabdir.tabs[i++].length = at->namelen;
    }

    if ( at->opbd!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('o','p','b','d');
	at->tabdir.tabs[i].data = at->opbd;
	at->tabdir.tabs[i++].length = at->opbdlen;
    }

    if ( at->post!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('p','o','s','t');
	at->tabdir.tabs[i].data = at->post;
	at->tabdir.tabs[i++].length = at->postlen;
    }

    if ( format!=ff_otf && format!=ff_otfcid && format!=ff_none ) {
	if ( at->prepf!=NULL ) {
	    at->tabdir.tabs[i].tag = CHR('p','r','e','p');
	    at->tabdir.tabs[i].data = at->prepf;
	    at->tabdir.tabs[i++].length = at->preplen;
	}
    }

    if ( at->prop!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('p','r','o','p');
	at->tabdir.tabs[i].data = at->prop;
	at->tabdir.tabs[i++].length = at->proplen;
    }

    if ( at->vheadf!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('v','h','e','a');
	at->tabdir.tabs[i].data = at->vheadf;
	at->tabdir.tabs[i++].length = at->vheadlen;

	at->tabdir.tabs[i].tag = CHR('v','m','t','x');
	at->tabdir.tabs[i].data = at->gi.vmtx;
	at->tabdir.tabs[i++].length = at->gi.vmtxlen;
    }

    if ( at->fvar!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('f','v','a','r');
	at->tabdir.tabs[i].data = at->fvar;
	at->tabdir.tabs[i++].length = at->fvarlen;
    }
    if ( at->gvar!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('g','v','a','r');
	at->tabdir.tabs[i].data = at->gvar;
	at->tabdir.tabs[i++].length = at->gvarlen;
    }
    if ( at->cvar!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('c','v','a','r');
	at->tabdir.tabs[i].data = at->cvar;
	at->tabdir.tabs[i++].length = at->cvarlen;
    }
    if ( at->avar!=NULL ) {
	at->tabdir.tabs[i].tag = CHR('a','v','a','r');
	at->tabdir.tabs[i].data = at->avar;
	at->tabdir.tabs[i++].length = at->avarlen;
    }

    if ( i>=MAX_TAB )
	IError("Miscalculation of number of tables needed. Up sizeof tabs array in struct tabdir in ttf.h" );

    for ( tab=sf->ttf_tab_saved; tab!=NULL && i<MAX_TAB; tab=tab->next ) {
	at->tabdir.tabs[i].tag = tab->tag;
	at->tabdir.tabs[i].data = tab->temp;
	at->tabdir.tabs[i++].length = tab->len;
    }
    if ( tab!=NULL )
	IError("Some user supplied tables omitted. Up sizeof tabs array in struct tabdir in ttf.h" );

    at->tabdir.numtab = i;
    at->tabdir.searchRange = (i<16?8:i<32?16:i<64?32:64)*16;
    at->tabdir.entrySel = (i<16?3:i<32?4:i<64?5:6);
    at->tabdir.rangeShift = at->tabdir.numtab*16-at->tabdir.searchRange;
}
