switch ( mi->mid ) {
	  case MID_RegenBitmaps:
	    mi->ti.disabled = mv->sf->bitmaps==NULL;
	  break;
	  case MID_CharInfo:
	    mi->ti.disabled = sc==NULL /*|| mv->fv->b.cidmaster!=NULL*/;
	  break;
	  case MID_ShowDependents:
	    mi->ti.disabled = sc==NULL || sc->dependents == NULL;
	  break;
	  case MID_FindProblems:
	  case MID_Transform:
	    mi->ti.disabled = sc==NULL;
	  break;
	  case MID_Effects:
	    mi->ti.disabled = sc==NULL || mv->sf->onlybitmaps || order2;
	  break;
	  case MID_RmOverlap: case MID_Stroke:
	    mi->ti.disabled = sc==NULL || mv->sf->onlybitmaps;
	  break;
	  case MID_AddExtrema:
	  case MID_Round: case MID_Correct:
	    mi->ti.disabled = sc==NULL || mv->sf->onlybitmaps;
	  break;
#ifdef FONTFORGE_CONFIG_TILEPATH
	  case MID_TilePath:
	    mi->ti.disabled = sc==NULL || mv->sf->onlybitmaps || ClipBoardToSplineSet()==NULL || order2;
	  break;
#endif
	  case MID_Simplify:
	    mi->ti.disabled = sc==NULL || mv->sf->onlybitmaps;
	  break;
	  case MID_BuildAccent:
	    anybuildable = false;
	    if ( sc!=NULL && SFIsSomethingBuildable(mv->sf,sc,mv->layer,false) )
		anybuildable = true;
	    mi->ti.disabled = !anybuildable;
	  break;
	  case MID_Autotrace:
	    mi->ti.disabled = !(FindAutoTraceName()!=NULL && sc!=NULL &&
		    sc->layers[ly_back].images!=NULL );
	  break;
	}
