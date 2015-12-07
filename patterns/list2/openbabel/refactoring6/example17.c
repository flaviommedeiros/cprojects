if ( TREE_IS_S_REACHABLE(prim(v)) /*Is_s_Reachable(prim(v)*/
                     /* if v' is reachable, an st-path is given by P(u)-uv-P'(v') */
                     /*&& PrevPt[prim(u)] != prim(v) ** avoid edges of T' */
                     && (SwitchEdge_Vert1(prim(u)) != prim(v) || SwitchEdge_Vert2(prim(u)) != prim(u)) /* avoid edges of T' */
                     && b_u != b_v
                     && !(pBNS->type_TACN && bIgnoreVertexNonTACN_group( pBNS, prim(v), u, SwitchEdge ))
#if ( FIX_KEEP_H_ON_NH_ANION == 1 )
                     && !(pBNS->type_TACN && bIsRemovedHfromNHaion( pBNS, prim(v), u ))
#endif
                     ) {
#if ( BNS_RAD_SEARCH == 1 )
                    n ++;
#endif
                     /* there is now a valid sv-path via u avoiding b_v (unless v==b_v)
                       => u, v, u', and v' now all become part of the same connected component of M[C] */
                    w = MakeBlossom( pBNS, ScanQ, &QSize, Pu, Pv, max_len_Pu_Pv, SwitchEdge, BasePtr, u, v, iuv, b_u, b_v, Tree );
                    /* this constructed the new blossom and returned its base */
                    if ( IS_BNS_ERROR( w ) ) {
                        pBD->QSize = QSize;
                        return w; /* error */
                    }
                    b_u = w; /* the new base of C(u) */
                    if ( prim(w) == Vertex_t ) {
                        /* t is now s-reachable, a valid augmenting path P exists in M */
                        delta = FindPathCap( pBNS, SwitchEdge, Vertex_s, Vertex_t, 10000 ); /* compute the residual capacity of P + P' */
                        if ( IS_BNS_ERROR( delta ) ) {
                            pBD->QSize = QSize;
                            return delta; /* error */
                        }
#if ( ALLOW_ONLY_SIMPLE_ALT_PATH == 1 )
                        if ( pBNS->bNotASimplePath || abs(delta) > 1 ) {
                            delta = 0;
                        }
#endif
                        if ( delta ) {
                            pBNS->bChangeFlow |= (bChangeFlow & BNS_EF_CHNG_FLOW);
                        }
                        ret = PullFlow( pBNS, SwitchEdge, Vertex_s, Vertex_t, delta, 0, bChangeFlow ); /* augment on a pair of valid st-paths */
                        pBD->QSize = QSize;
                        return ( IS_BNS_ERROR(ret)? ret : delta );
                    }
                }
