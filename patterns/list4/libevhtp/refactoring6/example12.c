if (
#ifdef USE_SUBEXP_CALL
      reg->num_call > 0 ||
#endif
      IS_QUANTIFIER_IN_REPEAT(qn)) {
    r = add_opcode(reg, qn->greedy ? OP_REPEAT_INC_SG : OP_REPEAT_INC_NG_SG);
  }
  else {
    r = add_opcode(reg, qn->greedy ? OP_REPEAT_INC : OP_REPEAT_INC_NG);
  }
