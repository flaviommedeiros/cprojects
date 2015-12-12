#ifdef R29_HACK
if(rs1[i]!=29||start<0x80001000||start>=0x80800000)
      #endif
      {
        jaddr=(int)out;
        #ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
        // Hint to branch predictor that the branch is unlikely to be taken
        if(rs1[i]>=28)
          emit_jno_unlikely(0);
        else
        #endif
        emit_jno(0);
      }
