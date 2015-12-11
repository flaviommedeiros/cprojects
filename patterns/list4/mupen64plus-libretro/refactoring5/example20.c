#ifdef DESTRUCTIVE_WRITEBACK
if(i_regmap[hr]!=regs[t].regmap_entry[hr] || ( !((regs[t].dirty>>hr)&1) && ((i_dirty>>hr)&1) && (((i_is32&~unneeded_reg_upper[t])>>i_regmap[hr])&1) ) || (((i_is32&~regs[t].was32&~unneeded_reg_upper[t])>>(i_regmap[hr]&63))&1)) {
        #else
        if(i_regmap[hr]!=regs[t].regmap_entry[hr] ) {
        #endif
          if(regs[t].regmap_entry[hr]==0) {
            emit_zeroreg(hr);
          }
          else if(regs[t].regmap_entry[hr]!=CCREG)
          {
            emit_loadreg(regs[t].regmap_entry[hr],hr);
          }
        }
      }
