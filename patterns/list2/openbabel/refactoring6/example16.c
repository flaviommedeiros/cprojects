if ( !(pBD             = (BN_DATA *) inchi_calloc( 1, sizeof(BN_DATA) ) ) ||
         !(pBD->BasePtr    = (Vertex *)  inchi_calloc( max_num_vertices, sizeof(Vertex) ) ) ||
         !(pBD->SwitchEdge = (Edge   *)  inchi_calloc( max_num_vertices, sizeof(Edge  ) ) ) ||
         !(pBD->Tree       = (S_CHAR *)  inchi_calloc( max_num_vertices, sizeof(S_CHAR) ) ) ||
         !(pBD->ScanQ      = (Vertex *)  inchi_calloc( max_num_vertices, sizeof(Vertex) ) ) ||
         !(pBD->Pu         = (Vertex *)  inchi_calloc( max_len_Pu_Pv,    sizeof(Vertex) ) ) ||
#if ( BNS_RAD_SEARCH == 1 )
         !(pBD->RadEndpoints = (Vertex *)   inchi_calloc( max_len_Pu_Pv, sizeof(Vertex) ) ) ||
         !(pBD->RadEdges     = (EdgeIndex*) inchi_calloc( max_len_Pu_Pv, sizeof(EdgeIndex) ) ) ||
#endif
         !(pBD->Pv         = (Vertex *)  inchi_calloc( max_len_Pu_Pv,    sizeof(Vertex) ) ) 
       ) {
        pBD = DeAllocateBnData( pBD );
    } else {
        /* Initialize data */
        ClearAllBnDataEdges(pBD->SwitchEdge, NO_VERTEX, max_num_vertices);
        ClearAllBnDataVertices(pBD->BasePtr, NO_VERTEX, max_num_vertices);
        memset(pBD->Tree, TREE_NOT_IN_M, max_num_vertices);
        pBD->QSize = -1;
        pBD->max_len_Pu_Pv    = max_len_Pu_Pv;
        pBD->max_num_vertices = max_num_vertices;
#if ( BNS_RAD_SEARCH == 1 )
        pBD->nNumRadEndpoints = 0;
#endif
    }
