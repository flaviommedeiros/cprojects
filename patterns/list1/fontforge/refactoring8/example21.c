void FVOverlap(FontViewBase *fv,enum overlap_type ot) {
    int i, cnt=0, layer, first, last, gid;
    SplineChar *sc;

    /* We know it's more likely that we'll find a problem in the overlap code */
    /*  than anywhere else, so let's save the current state against a crash */
    DoAutoSaves();

    for ( i=0; i<fv->map->enccount; ++i )
	if ( fv->selected[i] && (gid = fv->map->map[i])!=-1 &&
		SCWorthOutputting(fv->sf->glyphs[gid]) )
	    ++cnt;

    ff_progress_start_indicator(10,_("Removing overlaps..."),_("Removing overlaps..."),0,cnt,1);

    SFUntickAll(fv->sf);
    for ( i=0; i<fv->map->enccount; ++i ) if ( fv->selected[i] &&
	    (gid = fv->map->map[i])!=-1 &&
	    SCWorthOutputting((sc=fv->sf->glyphs[gid])) &&
	    !sc->ticked ) {
	sc->ticked = true;
#if 0
	// We await testing on the necessity of this operation.
	if ( !SCRoundToCluster(sc,ly_all,false,.03,.12))
	    SCPreserveLayer(sc,fv->active_layer,false);
#else
	    SCPreserveLayer(sc,fv->active_layer,false);
#endif // 0
	MinimumDistancesFree(sc->md);
	if ( sc->parent->multilayer ) {
	    first = ly_fore;
	    last = sc->layer_cnt-1;
	} else
	    first = last = fv->active_layer;
	for ( layer = first; layer<=last; ++layer )
	    sc->layers[layer].splines = SplineSetRemoveOverlap(sc,sc->layers[layer].splines,ot);
	SCCharChangedUpdate(sc,fv->active_layer);
	if ( !ff_progress_next())
    break;
    }
    ff_progress_end_indicator();
}
