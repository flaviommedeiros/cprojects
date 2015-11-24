static void _CVMenuOverlap(CharView *cv,enum overlap_type ot) {
    /* We know it's more likely that we'll find a problem in the overlap code */
    /*  than anywhere else, so let's save the current state against a crash */
    int layer = cv->b.drawmode == dm_grid ? ly_grid :
		cv->b.drawmode == dm_back ? ly_back
					: cv->b.layerheads[dm_fore] - cv->b.sc->layers;

    DoAutoSaves();
#if 0
    // We await testing on the necessity of this operation.
    if ( !SCRoundToCluster(cv->b.sc,layer,false,.03,.12))
	CVPreserveState(&cv->b);	/* SCRound2Cluster does this when it makes a change, not otherwise */
#else
    CVPreserveState(&cv->b);
#endif // 0
    if ( cv->b.drawmode==dm_fore ) {
	MinimumDistancesFree(cv->b.sc->md);
	cv->b.sc->md = NULL;
    }
    cv->b.layerheads[cv->b.drawmode]->splines = SplineSetRemoveOverlap(cv->b.sc,cv->b.layerheads[cv->b.drawmode]->splines,ot);
    CVCharChangedUpdate(&cv->b);
}
