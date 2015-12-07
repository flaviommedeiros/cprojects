if ( atom[nxt_at].valence != 3 
#if ( TAUT_RINGS_ATTACH_CHAIN == 1 )        
         || !atom[nxt_at].bCutVertex
#endif        
       ) {
        return 0;
    }
