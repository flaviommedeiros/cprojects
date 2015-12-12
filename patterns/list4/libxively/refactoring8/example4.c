static const byte avr_op_74_index[1 + 0x7ff] = {
  [0x9405 ^ 0x9000] = avr_op_index_ASR,        /* 1001 010d dddd 0101 | ASR */
  [0x9400 ^ 0x9000] = avr_op_index_COM,        /* 1001 010d dddd 0000 | COM */
  [0x940A ^ 0x9000] = avr_op_index_DEC,        /* 1001 010d dddd 1010 | DEC */
  [0x9006 ^ 0x9000] = avr_op_index_ELPM_Z,     /* 1001 000d dddd 0110 | ELPM */
  [0x9007 ^ 0x9000] = avr_op_index_ELPM_Z_incr,/* 1001 000d dddd 0111 | ELPM */
  [0x9403 ^ 0x9000] = avr_op_index_INC,        /* 1001 010d dddd 0011 | INC */
  [0x9000 ^ 0x9000] = avr_op_index_LDS,        /* 1001 000d dddd 0000 | LDS */
  [0x900C ^ 0x9000] = avr_op_index_LD_X,       /* 1001 000d dddd 1100 | LD */
  [0x900E ^ 0x9000] = avr_op_index_LD_X_decr,  /* 1001 000d dddd 1110 | LD */
  [0x900D ^ 0x9000] = avr_op_index_LD_X_incr,  /* 1001 000d dddd 1101 | LD */
  [0x900A ^ 0x9000] = avr_op_index_LD_Y_decr,  /* 1001 000d dddd 1010 | LD */
  [0x9009 ^ 0x9000] = avr_op_index_LD_Y_incr,  /* 1001 000d dddd 1001 | LD */
  [0x9002 ^ 0x9000] = avr_op_index_LD_Z_decr,  /* 1001 000d dddd 0010 | LD */
  [0x9001 ^ 0x9000] = avr_op_index_LD_Z_incr,  /* 1001 000d dddd 0001 | LD */
  [0x9004 ^ 0x9000] = avr_op_index_LPM_Z,      /* 1001 000d dddd 0100 | LPM */
  [0x9005 ^ 0x9000] = avr_op_index_LPM_Z_incr, /* 1001 000d dddd 0101 | LPM */
  [0x9406 ^ 0x9000] = avr_op_index_LSR,        /* 1001 010d dddd 0110 | LSR */
  [0x9401 ^ 0x9000] = avr_op_index_NEG,        /* 1001 010d dddd 0001 | NEG */
  [0x900F ^ 0x9000] = avr_op_index_POP,        /* 1001 000d dddd 1111 | POP */
#ifdef ISA_XMEGA
  [0x9204 ^ 0x9000] = avr_op_index_XCH,        /* 1001 001d dddd 0100 | XCH */
  [0x9205 ^ 0x9000] = avr_op_index_LAS,        /* 1001 001d dddd 0101 | LAS */
  [0x9206 ^ 0x9000] = avr_op_index_LAC,        /* 1001 001d dddd 0110 | LAC */
  [0x9207 ^ 0x9000] = avr_op_index_LAT,        /* 1001 001d dddd 0111 | LAT */
#endif // ISA_XMEGA
  [0x920F ^ 0x9000] = avr_op_index_PUSH,       /* 1001 001d dddd 1111 | PUSH */
  [0x9407 ^ 0x9000] = avr_op_index_ROR,        /* 1001 010d dddd 0111 | ROR */
  [0x9200 ^ 0x9000] = avr_op_index_STS,        /* 1001 001d dddd 0000 | STS */
  [0x920C ^ 0x9000] = avr_op_index_ST_X,       /* 1001 001d dddd 1100 | ST */
  [0x920E ^ 0x9000] = avr_op_index_ST_X_decr,  /* 1001 001d dddd 1110 | ST */
  [0x920D ^ 0x9000] = avr_op_index_ST_X_incr,  /* 1001 001d dddd 1101 | ST */
  [0x920A ^ 0x9000] = avr_op_index_ST_Y_decr,  /* 1001 001d dddd 1010 | ST */
  [0x9209 ^ 0x9000] = avr_op_index_ST_Y_incr,  /* 1001 001d dddd 1001 | ST */
  [0x9202 ^ 0x9000] = avr_op_index_ST_Z_decr,  /* 1001 001d dddd 0010 | ST */
  [0x9201 ^ 0x9000] = avr_op_index_ST_Z_incr,  /* 1001 001d dddd 0001 | ST */
  [0x9402 ^ 0x9000] = avr_op_index_SWAP,       /* 1001 010d dddd 0010 | SWAP */
};
