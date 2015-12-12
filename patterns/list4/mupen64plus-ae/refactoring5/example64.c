#ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
if(match&&(!branch_internal||!is_ds[(ba[i]-start)>>2])) {
          if(adj) {
            emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
            add_to_linker((int)out,ba[i],branch_internal);
          }else{
            emit_addnop(13);
            add_to_linker((int)out,ba[i],branch_internal*2);
          }
          emit_jmp(0);
        }else
        #endif
        {
          if(adj) emit_addimm(cc,-(int)CLOCK_DIVIDER*adj,cc);
          store_regs_bt(branch_regs[i].regmap,branch_regs[i].is32,branch_regs[i].dirty,ba[i]);
          load_regs_bt(branch_regs[i].regmap,branch_regs[i].is32,branch_regs[i].dirty,ba[i]);
          if(branch_internal)
            assem_debug("branch: internal");
          else
            assem_debug("branch: external");
          if(branch_internal&&is_ds[(ba[i]-start)>>2]) {
            ds_assemble_entry(i);
          }
          else {
            add_to_linker((int)out,ba[i],branch_internal);
            emit_jmp(0);
          }
        }
