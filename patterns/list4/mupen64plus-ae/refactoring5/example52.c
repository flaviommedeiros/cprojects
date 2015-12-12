#ifdef RAM_OFFSET
if((itype[i]==LOAD||opcode[i]==0x31||opcode[i]==0x35)&&(signed int)constmap[i][rs]+offset<(signed int)0x80800000) 
                emit_movimm(constmap[i][rs]+offset+(int)g_rdram-0x80000000,ra);
              else
              #endif
              emit_movimm(constmap[i][rs]+offset,ra);
