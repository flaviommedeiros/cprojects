#ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
if(match&&(!internal||!is_ds[(ba[i]-start)>>2])) {
          if(adj) {
            emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
            add_to_linker((intptr_t)out,ba[i],internal);
          }else{
            emit_addnop(13);
            add_to_linker((intptr_t)out,ba[i],internal*2);
          }
          emit_jmp(0);
        }else
        #endif
        {
          if(adj) emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
          store_regs_bt(branch_regs[i].regmap,branch_regs[i].is32,branch_regs[i].dirty,ba[i]);
          load_regs_bt(branch_regs[i].regmap,branch_regs[i].is32,branch_regs[i].dirty,ba[i]);
          if(internal)
            assem_debug("branch: internal");
          else
            assem_debug("branch: external");
          if(internal&&is_ds[(ba[i]-start)>>2]) {
            ds_assemble_entry(i);
          }
          else {
            add_to_linker((intptr_t)out,ba[i],internal);
            emit_jmp(0);
          }
        }
