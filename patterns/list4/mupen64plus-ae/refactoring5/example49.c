#ifdef RAM_OFFSET
if((signed int)constmap[i][rs]+offset<(signed int)0x80800000) 
                emit_movimm(((constmap[i][rs]+offset)&0xFFFFFFFC)+(int)g_rdram-0x80000000,ra);
              else
              #endif
              emit_movimm((constmap[i][rs]+offset)&0xFFFFFFFC,ra);
