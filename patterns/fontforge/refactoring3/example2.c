switch ( mi->mid ) {
	  case MID_FontInfo: case MID_CharInfo: case MID_ShowDependentRefs:
	  case MID_FindProblems:
	  case MID_AvailBitmaps:
	    mi->ti.disabled = cv->b.container!=NULL;
	  break;
	  case MID_GetInfo:
	    {
		SplinePoint *sp; SplineSet *spl; RefChar *ref; ImageList *img;
		mi->ti.disabled = !CVOneThingSel(cv,&sp,&spl,&ref,&img,&ap,&cp);
	    }
	  break;
	  case MID_CheckSelf:
	    mi->ti.checked = cv->checkselfintersects;
	  break;
	  case MID_GlyphSelfIntersects:
	    mi->ti.disabled = !cv->checkselfintersects;
	    mi->ti.checked = self_intersects==1;
	  break;
	  case MID_Clockwise:
	    mi->ti.disabled = !anypoints || dir==2 || dir<0;
	    mi->ti.checked = dir==1;
	  break;
	  case MID_Counter:
	    mi->ti.disabled = !anypoints || dir==2 || dir<0;
	    mi->ti.checked = dir==0;
	  break;
	  case MID_Correct:
	    mi->ti.disabled = (cv->b.layerheads[cv->b.drawmode]->splines==NULL && cv->b.layerheads[cv->b.drawmode]->refs==NULL) ||
		    dir==2 || self_intersects==1;
	  break;
	  case MID_ReverseDir:
	    mi->ti.disabled = !anypoints;
	  break;
	  case MID_Stroke:
	  case MID_RmOverlap:
	  case MID_Styles:
	    mi->ti.disabled = cv->b.layerheads[cv->b.drawmode]->splines==NULL ||
				cv->b.container!=NULL;
	  break;
#ifdef FONTFORGE_CONFIG_TILEPATH
	  case MID_TilePath:
	    mi->ti.disabled = badsel;
	  break;
#endif
	  case MID_RegenBitmaps: case MID_RemoveBitmaps:
	    mi->ti.disabled = cv->b.fv->sf->bitmaps==NULL;
	  break;
	  case MID_AddExtrema:
	    mi->ti.disabled = cv->b.layerheads[cv->b.drawmode]->splines==NULL || (cv->b.sc->inspiro && hasspiro());
	  /* Like Simplify, always available, but may not do anything if */
	  /*  all extrema have points. I'm not going to check for that, too hard */
	  break;
	  case MID_Simplify:
	    mi->ti.disabled = cv->b.layerheads[cv->b.drawmode]->splines==NULL || (cv->b.sc->inspiro && hasspiro());
	  /* Simplify is always available (it may not do anything though) */
	  /*  well, ok. Disable it if there is absolutely nothing to work on */
	  break;
	  case MID_BuildAccent:
	    mi->ti.disabled = !SFIsSomethingBuildable(cv->b.fv->sf,cv->b.sc,
		    CVLayer((CharViewBase *) cv),false);
	  break;
	  case MID_Autotrace:
	    mi->ti.disabled = FindAutoTraceName()==NULL || cv->b.sc->layers[ly_back].images==NULL;
	  break;
	  case MID_Align:
	    mi->ti.disabled = cv->b.sc->inspiro && hasspiro();
	  break;
	}
