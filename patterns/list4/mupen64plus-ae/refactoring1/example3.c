if(adj) emit_addimm(cc,-(int)CLOCK_DIVIDER*adj,cc);
        #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
        else if(match) emit_addnop(13);
#endif
