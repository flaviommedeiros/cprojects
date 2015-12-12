#ifdef HOST_IMM_ADDR32
if(itype[i+1]==RMW || (itype[i+1]==STORE && can_direct_write(constaddr)))
        #endif
        {
          if(itype[i+1]==LOAD&&can_direct_read(constaddr))
            emit_movimm(map_address(constaddr),ra);
          else
            emit_movimm(constaddr,ra);
        }
