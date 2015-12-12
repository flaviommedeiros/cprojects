#ifndef DESTRUCTIVE_WRITEBACK
if(ds)
        #endif
        for(hr=0;hr<HOST_REGS;hr++)
        {
          int r=current.regmap[hr];
          if(r>0&&r<64)
          {
            if((current.dirty>>hr)&((current.is32&~temp_is32)>>r)&1) {
              temp_is32|=1LL<<r;
              //DebugMessage(M64MSG_VERBOSE, "restore %d",r);
            }
          }
        }
