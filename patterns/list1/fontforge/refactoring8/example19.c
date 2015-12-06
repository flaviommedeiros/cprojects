void *__FreeTypeFontContext(FT_Library context,
	SplineFont *sf,SplineChar *sc,FontViewBase *fv,
	int layer,
	enum fontformat ff,int flags,void *shared_ftc) {
    /* build up a temporary font consisting of:
     *	sc!=NULL   => Just that character (and its references)
     *  fv!=NULL   => selected characters
     *  else	   => the entire font
     */
    FTC *ftc;
    SplineChar **old=sf->glyphs, **new;
    uint8 *selected = fv!=NULL ? fv->selected : NULL;
    EncMap *map = fv!=NULL ? fv->map : sf->fv!=NULL ? sf->fv->map : sf->map;
    int i,cnt, notdefpos;

    if ( context==NULL )
return( NULL );
    if ( sf->multilayer || sf->strokedfont )
return( NULL );

    ftc = calloc(1,sizeof(FTC));
    if ( shared_ftc!=NULL ) {
	*ftc = *(FTC *) shared_ftc;
	ftc->face = NULL;
	ftc->shared_ftc = shared_ftc;
	ftc->em = ((FTC *) shared_ftc)->em;
	ftc->layer = layer;
    } else {
	ftc->sf = sf;
	ftc->em = sf->ascent+sf->descent;
	ftc->file = NULL;
	ftc->layer = layer;

	ftc->file = tmpfile();
	if ( ftc->file==NULL ) {
	    free(ftc);
return( NULL );
	}

	old = sf->glyphs;
	notdefpos = SFFindNotdef(sf,-2);	/* Do this early */
	if ( sc!=NULL || selected!=NULL ) {
	    /* Build up a font consisting of those characters we actually use */
	    new = calloc(sf->glyphcnt,sizeof(SplineChar *));
	    if ( sc!=NULL )
		TransitiveClosureAdd(new,old,sc,layer);
	    else for ( i=0; i<map->enccount; ++i )
		if ( selected[i] && map->map[i]!=-1 &&
			SCWorthOutputting(old[map->map[i]]))
		    TransitiveClosureAdd(new,old,old[map->map[i]],layer);
	    /* Add these guys so we'll get reasonable blue values */
	    /* we won't rasterize them */
	    if ( PSDictHasEntry(sf->private,"BlueValues")==NULL ) {
		AddIf(sf,new,old,'I',layer);
		AddIf(sf,new,old,'O',layer);
		AddIf(sf,new,old,'x',layer);
		AddIf(sf,new,old,'o',layer);
	    }
	    if ( notdefpos!=-1 )
		TransitiveClosureAdd(new,old,sf->glyphs[notdefpos],layer);
		/* If there's a .notdef use it so that we don't generate our own .notdef (which can add cvt entries) */
	    /* Nifty bug. We might want to autohint some of the glyphs */
	    /* now that's going to cause various things to be remetricked */
	    /* like the metricsview, which may expect the full glyph set */
	    /* available, and will crash if that is not the case */
	    /* So if anything needs autohinting, do it now */
	    if ( (ff==ff_pfb || ff==ff_pfa || ff==ff_otf || ff==ff_otfcid || ff==ff_cff) &&
		    autohint_before_generate ) {
		extern int preserve_hint_undoes;	/* users don't expect that rasterizing the glyph will cause an undo */
		int phu = preserve_hint_undoes;		/* if metrics view & char view are open, and a change is made in */
							/*  the char view, then metrics view rasterize glyph, changes hints, */
							/*  adds a hint undo. And suddenly Undo does the wrong thing. It */
							/*  undoes the hint change (which the user probably hasn't noticed) */
							/*  and leaves the change the user did intact. And that will force */
							/*  another rasterize and perhaps another hint undo... */
		SplineChar *sc;
		BlueData bd;
		preserve_hint_undoes = false;
		QuickBlues(sf,layer,&bd);
		for ( i=0; i<sf->glyphcnt; ++i ) {
		    if ( (sc=new[i])!=NULL && sc->changedsincelasthinted &&
			    !sc->manualhints )
			SplineCharAutoHint(sc,layer,&bd);
		}
		preserve_hint_undoes = phu;
	    }
	    sf->glyphs = new;
	}
	sf->internal_temp = true;

    if (ff == ff_cff) {
        /* FT_New_Memory_Face does not like PS-wrapped CFF */
        flags |= ps_flag_nocffsugar;
    }

	switch ( ff ) {
	  case ff_pfb: case ff_pfa:
	    if ( !_WritePSFont(ftc->file,sf,ff,0,map,NULL,layer))
 goto fail;
	  break;
	  case ff_ttf: case ff_ttfsym:
	    ftc->isttf = true;
	    /* Fall through.... */
	  case ff_otf: case ff_otfcid: case ff_cff:
	    if ( !_WriteTTFFont(ftc->file,sf,ff,NULL,bf_none,flags,map,layer))
 goto fail;
	  break;
	  default:
 goto fail;
	}
	sf->internal_temp = false;

	if ( sf->subfontcnt!=0 ) {
	    /* can only be an otfcid */
	    int k, max=0;
	    for ( k=0; k<sf->subfontcnt; ++k )
		if ( sf->subfonts[k]->glyphcnt>max )
		    max = sf->subfonts[k]->glyphcnt;
	    ftc->glyph_indeces = malloc(max*sizeof(int));
	    memset(ftc->glyph_indeces,-1,max*sizeof(int));
	    for ( i=0; i<max; ++i ) {
		for ( k=0; k<sf->subfontcnt; ++k ) {
		    if ( i<sf->subfonts[k]->glyphcnt &&
			    SCWorthOutputting(sf->subfonts[k]->glyphs[i]) ) {
			ftc->glyph_indeces[i] = sf->subfonts[k]->glyphs[i]->ttf_glyph;
		break;
		    }
		}
	    }
	} else {
	    ftc->glyph_indeces = malloc(sf->glyphcnt*sizeof(int));
	    memset(ftc->glyph_indeces,-1,sf->glyphcnt*sizeof(int));
	    cnt = 1;
	    if ( notdefpos!=-1 )
		ftc->glyph_indeces[notdefpos] = 0;
	    if ( ff==ff_pfa || ff==ff_pfb ) {
		for ( i=0 ; i<sf->glyphcnt; ++i ) {
		    if ( i!=notdefpos && SCWorthOutputting(sf->glyphs[i]))
			ftc->glyph_indeces[i] = cnt++;
		}
	    } else {
		for ( i=0 ; i<sf->glyphcnt; ++i ) {
		    if ( SCWorthOutputting(sf->glyphs[i]) ) {
			ftc->glyph_indeces[i] = sf->glyphs[i]->ttf_glyph;
		    }
		}
	    }
	}

	fseek(ftc->file,0,SEEK_END);
	ftc->len = ftell(ftc->file);
#if defined (__MINGW32__)
        ftc->mappedfile = NULL;
        {
            int fd = _fileno(ftc->file);
            if (fd != -1) {
                HANDLE handle = CreateFileMapping((HANDLE)_get_osfhandle(fd), 
                                    NULL, PAGE_READONLY, 0, ftc->len, NULL);
                if (handle != NULL) {
                    ftc->mappedfile = MapViewOfFile(handle, FILE_MAP_READ,
                                        0, 0, ftc->len);
                    CloseHandle(handle);
                }
            }
            if (ftc->mappedfile == NULL)
                goto fail;
        }
#else
	ftc->mappedfile = mmap(NULL,ftc->len,PROT_READ,MAP_PRIVATE,fileno(ftc->file),0);
	if ( ftc->mappedfile==MAP_FAILED )
 goto fail;
#endif
	if ( sf->glyphs!=old ) {
	    free(sf->glyphs);
	    sf->glyphs = old;
	}
    }

    if ( FT_New_Memory_Face(context,ftc->mappedfile,ftc->len,0,&ftc->face))
 goto fail;
    GlyphHashFree(sf);		/* If we created a tiny font, our hash table may reflect that */
    
return( ftc );

 fail:
    sf->internal_temp = false;
    GlyphHashFree(sf);
    FreeTypeFreeContext(ftc);
    if ( sf->glyphs!=old ) {
	free(sf->glyphs);
	sf->glyphs = old;
    }
return( NULL );
}
