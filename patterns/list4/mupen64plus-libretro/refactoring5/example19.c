#ifdef RAM_OFFSET
if((signed int)constmap[i][hr]+imm[i+1]<(signed int)0x80800000)
          *value=constmap[i][hr]+imm[i+1]+(intptr_t)g_rdram-0x80000000;
        else
        #endif
        // Precompute load address
        *value=constmap[i][hr]+imm[i+1];
