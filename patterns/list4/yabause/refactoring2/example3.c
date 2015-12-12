#ifdef HOST_IMM_ADDR32
if(!can_direct_read(cpmap[i][hr]+imm[i+1]))
            #endif
            {
              int value=cpmap[i][hr]+imm[i+1];
              if(can_direct_read(value)) value=map_address(value);
              if((opcode2[i+1]&3)==0) value^=1; // byteswap for little-endian
              emit_movimm(value,hr);
            }
