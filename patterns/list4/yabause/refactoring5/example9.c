#ifdef CORTEX_A8_BRANCH_PREDICTION_HACK
if(match&&(!internal||!is_ds[(ba[i]-start)>>1])) {
        if(adj) {
          emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
          add_to_linker((int)out,ba[i],internal);
        }else{
          emit_addnop(13);
          add_to_linker((int)out,ba[i],internal*2);
        }
        emit_jmp(0);
      }else
      #endif
      {
        if(adj) emit_addimm(cc,-CLOCK_DIVIDER*adj,cc);
        store_regs_bt(regs[i].regmap,regs[i].dirty,ba[i]);
        load_regs_bt(regs[i].regmap,regs[i].dirty,ba[i]);
        if(internal)
          assem_debug("branch: internal\n");
        else
          assem_debug("branch: external\n");
        if(internal&&is_ds[(ba[i]-start)>>1]) {
          ds_assemble_entry(i);
        }
        else {
          add_to_linker((int)out,ba[i],internal);
          emit_jmp(0);
        }
      }
