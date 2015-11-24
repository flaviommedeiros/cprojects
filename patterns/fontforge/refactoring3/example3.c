switch ( mi->mid ) {
	  case MID_FontInfo:
	    mi->ti.disabled = in_modal;
	  break;
	  case MID_CharInfo:
	    mi->ti.disabled = anychars<0 || (gid = fv->b.map->map[anychars])==-1 ||
		    (fv->b.cidmaster!=NULL && fv->b.sf->glyphs[gid]==NULL) ||
		    in_modal;
	  break;
	  case MID_Transform:
	    mi->ti.disabled = anychars==-1;
	    /* some Transformations make sense on bitmaps now */
	  break;
	  case MID_AddExtrema:
	    mi->ti.disabled = anychars==-1 || fv->b.sf->onlybitmaps;
	  break;
	  case MID_Simplify:
	  case MID_Stroke: case MID_RmOverlap:
	    mi->ti.disabled = anychars==-1 || fv->b.sf->onlybitmaps;
	  break;
	  case MID_Styles:
	    mi->ti.disabled = anychars==-1 || fv->b.sf->onlybitmaps;
	  break;
	  case MID_Round: case MID_Correct:
	    mi->ti.disabled = anychars==-1 || fv->b.sf->onlybitmaps;
	  break;
#ifdef FONTFORGE_CONFIG_TILEPATH
	  case MID_TilePath:
	    mi->ti.disabled = anychars==-1 || fv->b.sf->onlybitmaps;
	  break;
#endif
	  case MID_AvailBitmaps:
	    mi->ti.disabled = fv->b.sf->mm!=NULL;
	  break;
	  case MID_RegenBitmaps: case MID_RemoveBitmaps:
	    mi->ti.disabled = fv->b.sf->bitmaps==NULL || fv->b.sf->onlybitmaps ||
		    fv->b.sf->mm!=NULL;
	  break;
	  case MID_BuildAccent:
	    anybuildable = false;
	    if ( anychars!=-1 ) {
		int i;
		for ( i=0; i<fv->b.map->enccount; ++i ) if ( fv->b.selected[i] ) {
		    SplineChar *sc=NULL, dummy;
		    gid = fv->b.map->map[i];
		    if ( gid!=-1 )
			sc = fv->b.sf->glyphs[gid];
		    if ( sc==NULL )
			sc = SCBuildDummy(&dummy,fv->b.sf,fv->b.map,i);
		    if ( SFIsSomethingBuildable(fv->b.sf,sc,fv->b.active_layer,false) ||
			    SFIsDuplicatable(fv->b.sf,sc)) {
			anybuildable = true;
		break;
		    }
		}
	    }
	    mi->ti.disabled = !anybuildable;
	  break;
	  case MID_Autotrace:
	    anytraceable = false;
	    if ( FindAutoTraceName()!=NULL && anychars!=-1 ) {
		int i;
		for ( i=0; i<fv->b.map->enccount; ++i )
		    if ( fv->b.selected[i] && (gid = fv->b.map->map[i])!=-1 &&
			    fv->b.sf->glyphs[gid]!=NULL &&
			    fv->b.sf->glyphs[gid]->layers[ly_back].images!=NULL ) {
			anytraceable = true;
		break;
		    }
	    }
	    mi->ti.disabled = !anytraceable;
	  break;
	  case MID_MergeFonts:
	    mi->ti.disabled = fv->b.sf->bitmaps!=NULL && fv->b.sf->onlybitmaps;
	  break;
	  case MID_FontCompare:
	    mi->ti.disabled = fv_list->b.next==NULL;
	  break;
	  case MID_InterpolateFonts:
	    mi->ti.disabled = fv->b.sf->onlybitmaps;
	  break;
	}
