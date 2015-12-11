#ifndef RAM_OFFSET
if(using_tlb)
  #endif
  {
    int earliest_available[HOST_REGS];
    int loop_start[HOST_REGS];
    int score[HOST_REGS];
    int end[HOST_REGS];
    int reg=using_tlb?MMREG:ROREG;

    // Init
    for(hr=0;hr<HOST_REGS;hr++) {
      score[hr]=0;earliest_available[hr]=0;
      loop_start[hr]=MAXBLOCK;
    }
    for(i=0;i<slen-1;i++)
    {
      // Can't do anything if no registers are available
      if(count_free_regs(regs[i].regmap)<=minimum_free_regs[i]) {
        for(hr=0;hr<HOST_REGS;hr++) {
          score[hr]=0;earliest_available[hr]=i+1;
          loop_start[hr]=MAXBLOCK;
        }
      }
      if(itype[i]==UJUMP||itype[i]==RJUMP||itype[i]==CJUMP||itype[i]==SJUMP||itype[i]==FJUMP) {
        if(!ooo[i]) {
          if(count_free_regs(branch_regs[i].regmap)<=minimum_free_regs[i+1]) {
            for(hr=0;hr<HOST_REGS;hr++) {
              score[hr]=0;earliest_available[hr]=i+1;
              loop_start[hr]=MAXBLOCK;
            }
          }
        }else{
          if(count_free_regs(regs[i].regmap)<=minimum_free_regs[i+1]) {
            for(hr=0;hr<HOST_REGS;hr++) {
              score[hr]=0;earliest_available[hr]=i+1;
              loop_start[hr]=MAXBLOCK;
            }
          }
        }
      }
      // Mark unavailable registers
      for(hr=0;hr<HOST_REGS;hr++) {
        if(regs[i].regmap[hr]>=0) {
          score[hr]=0;earliest_available[hr]=i+1;
          loop_start[hr]=MAXBLOCK;
        }
        if(itype[i]==UJUMP||itype[i]==RJUMP||itype[i]==CJUMP||itype[i]==SJUMP||itype[i]==FJUMP) {
          if(branch_regs[i].regmap[hr]>=0) {
            score[hr]=0;earliest_available[hr]=i+2;
            loop_start[hr]=MAXBLOCK;
          }
        }
      }
      // No register allocations after unconditional jumps
      if(itype[i]==UJUMP||itype[i]==RJUMP||(source[i]>>16)==0x1000)
      {
        for(hr=0;hr<HOST_REGS;hr++) {
          score[hr]=0;earliest_available[hr]=i+2;
          loop_start[hr]=MAXBLOCK;
        }
        i++; // Skip delay slot too
        //DebugMessage(M64MSG_VERBOSE, "skip delay slot: %x",start+i*4);
      }
      else
      // Possible match
      if(itype[i]==LOAD||itype[i]==LOADLR||
         itype[i]==STORE||itype[i]==STORELR||itype[i]==C1LS) {
        for(hr=0;hr<HOST_REGS;hr++) {
          if(hr!=EXCLUDE_REG) {
            end[hr]=i-1;
            for(j=i;j<slen-1;j++) {
              if(regs[j].regmap[hr]>=0) break;
              if(itype[j]==UJUMP||itype[j]==RJUMP||itype[j]==CJUMP||itype[j]==SJUMP||itype[j]==FJUMP) {
                if(branch_regs[j].regmap[hr]>=0) break;
                if(ooo[j]) {
                  if(count_free_regs(regs[j].regmap)<=minimum_free_regs[j+1]) break;
                }else{
                  if(count_free_regs(branch_regs[j].regmap)<=minimum_free_regs[j+1]) break;
                }
              }
              else if(count_free_regs(regs[j].regmap)<=minimum_free_regs[j]) break;
              if(itype[j]==UJUMP||itype[j]==RJUMP||itype[j]==CJUMP||itype[j]==SJUMP||itype[j]==FJUMP) {
                int t=(ba[j]-start)>>2;
                if(t<j&&t>=earliest_available[hr]) {
                  if(t==1||(t>1&&itype[t-2]!=UJUMP&&itype[t-2]!=RJUMP)||(t>1&&rt1[t-2]!=31)) { // call/ret assumes no registers allocated
                    // Score a point for hoisting loop invariant
                    if(t<loop_start[hr]) loop_start[hr]=t;
                    //DebugMessage(M64MSG_VERBOSE, "set loop_start: i=%x j=%x (%x)",start+i*4,start+j*4,start+t*4);
                    score[hr]++;
                    end[hr]=j;
                  }
                }
                else if(t<j) {
                  if(regs[t].regmap[hr]==reg) {
                    // Score a point if the branch target matches this register
                    score[hr]++;
                    end[hr]=j;
                  }
                }
                if(itype[j+1]==LOAD||itype[j+1]==LOADLR||
                   itype[j+1]==STORE||itype[j+1]==STORELR||itype[j+1]==C1LS) {
                  score[hr]++;
                  end[hr]=j;
                }
              }
              if(itype[j]==UJUMP||itype[j]==RJUMP||(source[j]>>16)==0x1000)
              {
                // Stop on unconditional branch
                break;
              }
              else
              if(itype[j]==LOAD||itype[j]==LOADLR||
                 itype[j]==STORE||itype[j]==STORELR||itype[j]==C1LS) {
                score[hr]++;
                end[hr]=j;
              }
            }
          }
        }
        // Find highest score and allocate that register
        int maxscore=0;
        for(hr=0;hr<HOST_REGS;hr++) {
          if(hr!=EXCLUDE_REG) {
            if(score[hr]>score[maxscore]) {
              maxscore=hr;
              //DebugMessage(M64MSG_VERBOSE, "highest score: %d %d (%x->%x)",score[hr],hr,start+i*4,start+end[hr]*4);
            }
          }
        }
        if(score[maxscore]>1)
        {
          if(i<loop_start[maxscore]) loop_start[maxscore]=i;
          for(j=loop_start[maxscore];j<slen&&j<=end[maxscore];j++) {
            //if(regs[j].regmap[maxscore]>=0) {DebugMessage(M64MSG_ERROR, "oops: %x %x was %d=%d",loop_start[maxscore]*4+start,j*4+start,maxscore,regs[j].regmap[maxscore]);}
            assert(regs[j].regmap[maxscore]<0);
            if(j>loop_start[maxscore]) regs[j].regmap_entry[maxscore]=reg;
            regs[j].regmap[maxscore]=reg;
            regs[j].dirty&=~(1<<maxscore);
            regs[j].wasconst&=~(1<<maxscore);
            regs[j].isconst&=~(1<<maxscore);
            if(itype[j]==UJUMP||itype[j]==RJUMP||itype[j]==CJUMP||itype[j]==SJUMP||itype[j]==FJUMP) {
              branch_regs[j].regmap[maxscore]=reg;
              branch_regs[j].wasdirty&=~(1<<maxscore);
              branch_regs[j].dirty&=~(1<<maxscore);
              branch_regs[j].wasconst&=~(1<<maxscore);
              branch_regs[j].isconst&=~(1<<maxscore);
              if(itype[j]!=RJUMP&&itype[j]!=UJUMP&&(source[j]>>16)!=0x1000) {
                regmap_pre[j+2][maxscore]=reg;
                regs[j+2].wasdirty&=~(1<<maxscore);
              }
              // loop optimization (loop_preload)
              int t=(ba[j]-start)>>2;
              if(t==loop_start[maxscore]) {
                if(t==1||(t>1&&itype[t-2]!=UJUMP&&itype[t-2]!=RJUMP)||(t>1&&rt1[t-2]!=31)) // call/ret assumes no registers allocated
                  regs[t].regmap_entry[maxscore]=reg;
              }
            }
            else
            {
              if(j<1||(itype[j-1]!=RJUMP&&itype[j-1]!=UJUMP&&itype[j-1]!=CJUMP&&itype[j-1]!=SJUMP&&itype[j-1]!=FJUMP)) {
                regmap_pre[j+1][maxscore]=reg;
                regs[j+1].wasdirty&=~(1<<maxscore);
              }
            }
          }
          i=j-1;
          if(itype[j-1]==RJUMP||itype[j-1]==UJUMP||itype[j-1]==CJUMP||itype[j-1]==SJUMP||itype[j-1]==FJUMP) i++; // skip delay slot
          for(hr=0;hr<HOST_REGS;hr++) {
            score[hr]=0;earliest_available[hr]=i+i;
            loop_start[hr]=MAXBLOCK;
          }
        }
      }
    }
  }
