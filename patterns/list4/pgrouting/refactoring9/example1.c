static int tomanysp_dijkstra_dist(char* sql, int start_vertex, 
         int *end_vertices, int nb_targets, bool directed, 
         bool has_reverse_cost, 
#ifdef PGR_MERGE
         pgr_cost_t **dists,
#else
         dist_fromto_t **dists,
#endif
         int *path_count) 
{

    int SPIcode;
    void *SPIplan;
    Portal SPIportal;
    bool moredata = TRUE;
    int ntuples;
    edge_t *edges = NULL;
    int total_tuples = 0;
    edge_columns_t edge_columns = {.id= -1, .source= -1, .target= -1, 
                                   .cost= -1, .reverse_cost= -1};
    int v_max_id=0;
    int v_min_id=INT_MAX;

    int sumFoundTargets = 0, numTarget;

    int s_count = 0;
    int t_count[nb_targets];
    for (numTarget = 0; numTarget < nb_targets; numTarget++)
        t_count[numTarget] = 0;

    char *err_msg;
    int ret = -1;
    register int z;
    int zcnt = 0;


    DBG("start shortest_path\n");

    SPIcode = SPI_connect();
    if (SPIcode  != SPI_OK_CONNECT) {
        elog(ERROR, "shortest_path: couldn't open a connection to SPI");
        return -1;
    }

    SPIplan = SPI_prepare(sql, 0, NULL);
    if (SPIplan  == NULL) {
        elog(ERROR, "shortest_path: couldn't create query plan via SPI");
        return -1;
    }

    if ((SPIportal = SPI_cursor_open(NULL, SPIplan, NULL, NULL, true)) == NULL) {
        elog(ERROR, "shortest_path: SPI_cursor_open('%s') returns NULL", sql);
        return -1;
    }

    DBG("Maybe there is moredata...\n");

    while (moredata == TRUE) {
        SPI_cursor_fetch(SPIportal, TRUE, TUPLIMIT);

        if (edge_columns.id == -1) {
            if (fetch_edge_columns(SPI_tuptable, &edge_columns, 
                                 has_reverse_cost) == -1)
            return finish(SPIcode, ret);
        }

        ntuples = SPI_processed;
        total_tuples += ntuples;
        if (!edges)
            edges = palloc(total_tuples * sizeof(edge_t));
        else
            edges = repalloc(edges, total_tuples * sizeof(edge_t));

        if (edges == NULL) {
            elog(ERROR, "Out of memory");
            return finish(SPIcode, ret);      
        }

        if (ntuples > 0) {
            int t;
            SPITupleTable *tuptable = SPI_tuptable;
            TupleDesc tupdesc = SPI_tuptable->tupdesc;

            for (t = 0; t < ntuples; t++) 
            {
                HeapTuple tuple = tuptable->vals[t];
                fetch_edge(&tuple, &tupdesc, &edge_columns, 
                         &edges[total_tuples - ntuples + t]);
            }
            SPI_freetuptable(tuptable);
        } 
        else {
            moredata = FALSE;
        }
    }

    //defining min and max vertex id

    DBG("Total %i tuples", total_tuples);

    for(z=0; z<total_tuples; z++) {
        if(edges[z].source<v_min_id)
            v_min_id=edges[z].source;

        if(edges[z].source>v_max_id)
            v_max_id=edges[z].source;

        if(edges[z].target<v_min_id)
            v_min_id=edges[z].target;

        if(edges[z].target>v_max_id)
            v_max_id=edges[z].target;      

        // DBG("%i <-> %i", v_min_id, v_max_id);

    }

    //::::::::::::::::::::::::::::::::::::  
    //:: reducing vertex id (renumbering)
    //::::::::::::::::::::::::::::::::::::


    for (numTarget = 0; numTarget < nb_targets; numTarget ++) {
        t_count[numTarget] = 0;
    }

    for(z=0; z<total_tuples; z++) {
        //check if edges[] contains source and target
        if(edges[z].source == start_vertex || edges[z].target == start_vertex)
            ++s_count;
        for (numTarget = 0; numTarget < nb_targets; numTarget++) {
            if (edges[z].source == end_vertices[numTarget] ||
                    edges[z].target == end_vertices[numTarget]) {
                ++t_count[numTarget];
                ++sumFoundTargets;    
            }
        }
        edges[z].source-=v_min_id;
        edges[z].target-=v_min_id;
        //  DBG("%i - %i", edges[z].source, edges[z].target);      
    }

    DBG("Total %i tuples", total_tuples);

    if(s_count == 0) {
        elog(ERROR, "Start vertex was not found.");
        return -1;
    }

    for (numTarget = 0; numTarget < nb_targets; numTarget++) {
        if(t_count[numTarget] == 0) zcnt++;
        DBG("t_count[%d] = %d", end_vertices[numTarget], t_count[numTarget]);
    }
    if (zcnt > 0) {
        elog(ERROR, "One of the target vertices was not found or several targets are the same.");
    }

    if(sumFoundTargets == 0 ) {
        elog(ERROR, "None of the target vertices has been found; aborting!");
        return -1;
    }

    DBG("Calling boost_dijkstra\n");

    start_vertex -= v_min_id;
    for (numTarget = 0; numTarget < nb_targets; numTarget++) {
        end_vertices[numTarget] -= v_min_id;
    }

    ret = onetomany_dijkstra_boostdist(edges, total_tuples, start_vertex,
                end_vertices, nb_targets, directed, has_reverse_cost,
                dists, &err_msg);

    DBG("ret = %i\n", ret);

    if (ret < 0) {
        //elog(ERROR, "Error computing path: %s", err_msg);
        ereport(ERROR, (errcode(ERRCODE_E_R_E_CONTAINING_SQL_NOT_PERMITTED), 
            errmsg("Error computing path: %s", err_msg)));
    } 

    //::::::::::::::::::::::::::::::::
    //:: restoring original vertex id
    //::::::::::::::::::::::::::::::::
    for(z=0; z<nb_targets; z++) {
#ifdef PGR_MERGE
        (*dists)[z].id1 += v_min_id;
        (*dists)[z].id2 += v_min_id;
#else
        (*dists)[z].vertex_id_source += v_min_id;
        (*dists)[z].vertex_id_target += v_min_id;
#endif
    }

    *path_count = nb_targets;

    return finish(SPIcode, ret);
}
