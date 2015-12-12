#ifdef HOST_IMM_ADDR32
if(itype[i]==RMW || (itype[i]==STORE && can_direct_write(constaddr)))
            #endif
            {
              if(itype[i]==LOAD&&can_direct_read(constaddr))
                emit_movimm(map_address(constaddr),ra);
              else
                emit_movimm(constaddr,ra);
            }
